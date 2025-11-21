#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ------------------------
// CONFIGURAÇÕES DO HARDWARE
// ------------------------

#define DHTPIN 4          // Pino do DHT22
#define DHTTYPE DHT22

#define MQ135_PIN 34      // Pino analógico MQ-135
#define LED_PIN 25        // LED vermelho
#define BUZZER_PIN 26     // Buzzer ativo (não passivo)

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ------------------------
// LIMITES DE ALERTA
// ------------------------

#define LIMITE_TEMPERATURA 30.0
#define LIMITE_GAS         100

// ------------------------
// CONFIGURAÇÕES DA REDE E MQTT
// ------------------------

const char* ssid = "seu wifi";
const char* password = "suasenha";
const char* mqtt_server = "192.168. xxxx"; // IP do seu Broker Mosquitto

WiFiClient espClient;
PubSubClient client(espClient);

// ------------------------
// TOPICOS MQTT
// ------------------------

const char* topicoTemperatura = "hissopo/sensor/temperatura";
const char* topicoUmidade    = "hissopo/sensor/umidade";
const char* topicoGas        = "hissopo/sensor/gas";

const char* topicoLedSet     = "hissopo/atuador/led/set";
const char* topicoBuzzerSet  = "hissopo/atuador/buzzer/set";

// ------------------------
// CALLBACK MQTT (RECEBE COMANDOS)
// ------------------------

void callback(char* topic, byte* message, unsigned int length) {
  
  String msg;
  for (int i = 0; i < length; i++) msg += (char)message[i];
  msg.trim();
  msg.toUpperCase();

  Serial.print("Comando recebido: ");
  Serial.println(msg);

  // Controle LED
  if (String(topic) == topicoLedSet) {
    digitalWrite(LED_PIN, (msg == "ON") ? HIGH : LOW);
  }

  // Controle buzzer
  if (String(topic) == topicoBuzzerSet) {
    if (msg == "ON") tone(BUZZER_PIN, 1000);
    else noTone(BUZZER_PIN);
  }
}

// ------------------------
// FUNÇÃO PARA RECONEXÃO MQTT
// ------------------------

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT... ");
    if (client.connect("HissopoClient")) {

      Serial.println("Conectado!");

      client.subscribe(topicoLedSet);
      client.subscribe(topicoBuzzerSet);

    } else {
      Serial.print("Falhou. Código: ");
      Serial.println(client.state());
      delay(1500);
    }
  }
}

// ------------------------
// SETUP
// ------------------------

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);

  Wire.begin();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");

  dht.begin();

  // Conectando WiFi
  WiFi.begin(ssid, password);
  lcd.setCursor(0, 1);
  lcd.print("WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }

  lcd.clear();
  lcd.print("WiFi Conectado!");

  delay(1000);

  // MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

// ------------------------
// LOOP PRINCIPAL
// ------------------------

void loop() {

  if (!client.connected()) reconnect();
  client.loop();

  // Ler sensores
  float temp = dht.readTemperature();
  float umid = dht.readHumidity();
  int gasRaw = analogRead(MQ135_PIN);

  // Verifica se DHT22 falhou
  if (isnan(temp) || isnan(umid)) {

    Serial.println("Falha ao ler DHT22");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro no DHT22");

    delay(1500);
    return;
  }

  Serial.print("Temp: "); Serial.println(temp);
  Serial.print("Umid: "); Serial.println(umid);
  Serial.print("Gas: "); Serial.println(gasRaw);

  // -----------------------------------
  // ALERTAS AUTOMATICOS
  // -----------------------------------

  bool alerta = false;

  if (temp >= LIMITE_TEMPERATURA) alerta = true;
  if (gasRaw >= LIMITE_GAS) alerta = true;

  if (alerta) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000); // buzzer ativo
  } else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  // Publicar MQTT
  client.publish(topicoTemperatura, String(temp).c_str());
  client.publish(topicoUmidade, String(umid).c_str());
  client.publish(topicoGas, String(gasRaw).c_str());

  // LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print(" U:");
  lcd.print(umid, 1);

  lcd.setCursor(0, 1);
  lcd.print("Gas:");
  lcd.print(gasRaw);

  delay(1500);
}
