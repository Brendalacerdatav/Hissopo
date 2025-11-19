🧪 Projeto Hissopo – Monitoramento Ambiental IoT

Sistema de monitoramento ambiental baseado em ESP32, utilizando os sensores DHT22 (temperatura e umidade) e MQ-135 (qualidade do ar), com comunicação via protocolo MQTT (Mosquitto).
O projeto permite visualizar os valores em tempo real e acionar atuadores (LED vermelho e buzzer) remotamente via clientes MQTT.

📌 1. Objetivo

Desenvolver um protótipo IoT de baixo custo capaz de monitorar temperatura, umidade e concentração de gases, transmitindo os dados para um broker MQTT e acionando alertas visuais e sonoros automaticamente ou por comandos remotos.

🧱 2. Arquitetura Geral do Sistema

Microcontrolador: ESP32 DOIT DevKit V1

Sensores:

DHT22 — temperatura e umidade

MQ-135 — detecção de gases (qualidade do ar)

Atuadores:

LED vermelho (alerta visual)

Buzzer ativo (alerta sonoro)

Display: LCD 16x2 I2C

Comunicação: Wi-Fi + MQTT

Broker: Mosquitto (executando localmente)

Clientes MQTT: MQTT Explorer, Node-RED, entre outros.

🧩 3. Estrutura do Repositório
hissopo/

── README.md
── /codigo/
   ├── hissopo.ino
   ├── bibliotecas.txt
   └── credenciais-exemplo.h

── /hardware/
   ├── esquema_fritzing.fzz
   ├── esquema_fritzing.png
   ├── lista_componentes.md
   └── fotos_montagem/

── /documentacao/
   ├── artigo_final.pdf
   ├── fluxograma.png
   ├── topicos_mqtt.png
   ├── diagramas/
   └── resultados/

── /testes/
  ├── tempos_resposta.csv
  ├── graficos/
  └── metodologia_testes.md

└── /video/
    └── link-video.txt

🔌 4. Lista de Componentes

- ESP32 DOIT DevKit V1

- Sensor DHT22

- Sensor MQ-135

- Display LCD 16x2 I2C

- LED vermelho

- Buzzer ativo

- Resistor 220 Ω

- Divisor de tensão (10 kΩ + 20 kΩ)

- Protoboard

- Jumpers

- Cabo USB

🛠 5. Instalação das Bibliotecas

As bibliotecas utilizadas estão listadas no arquivo /codigo/bibliotecas.txt.

Instale via Arduino IDE → Sketch → Incluir Biblioteca → Gerenciar Bibliotecas:

DHT sensor library

Adafruit Unified Sensor

LiquidCrystal_I2C

PubSubClient

Wire

WiFi

📡 6. Configuração do Mosquitto (Broker MQTT)
Instalação (Windows/Linux/macOS)

https://mosquitto.org/download/

Iniciar o broker
mosquitto

Teste simples

Em dois terminais:

Terminal 1 – assinando dados

mosquitto_sub -t hissopo/# 


Terminal 2 – publicando

mosquitto_pub -t hissopo/teste -m "ola"

🔧 7. Configuração do Código

Crie o arquivo /codigo/credenciais.h baseado em credenciais-exemplo.h:

#define WIFI_SSID "SEU_WIFI"
#define WIFI_PASSWORD "SUA_SENHA"
#define MQTT_SERVER "192.168.0.10"  // IP do computador com Mosquitto
#define MQTT_PORT 1883


Importante:
❌ Não suba suas credenciais reais no GitHub.

📤 8. Como carregar o código no ESP32

Abra o arquivo hissopo.ino

Conecte o ESP32 via USB

Vá em:
Ferramentas → Placa → ESP32 Dev Module

Clique em Upload

🛰 9. Tópicos MQTT utilizados

O ESP32 usa os seguintes tópicos:

📥 Publicações (do ESP32 → broker)

hissopo/sensor/temperatura

hissopo/sensor/umidade

hissopo/sensor/gas

📤 Assinaturas (brokers/cliente → ESP32)

hissopo/atuador/led/set

hissopo/atuador/buzzer/set

⭐ 10. Como testar com MQTT Explorer

Instale: https://mqtt-explorer.com

Conecte ao endereço do seu Mosquitto

Observe os tópicos sendo atualizados em tempo real

Envie comandos:

LED:

hissopo/atuador/led/set → "ON"


Buzzer:

hissopo/atuador/buzzer/set → "OFF"

📊 11. Resultados e Testes

Os testes de:

tempo de resposta de sensores

tempo de acionamento dos atuadores

latência MQTT

estão documentados em /testes/ com tabelas, gráficos e metodologia.

🎥 12. Vídeo de Demonstração

O link para o vídeo não listado no YouTube está no arquivo:

/video/link-video.txt

📚 13. Artigo Científico

A versão final do artigo está em:

/documentacao/artigo_final.pdf

👤 14. Autoria

Projeto desenvolvido por:

Brenda Ribeiro Lacerda Tavares
Universidade Presbiteriana Mackenzie – ADS – Objetos Inteligentes Conectados
