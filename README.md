🧪 Projeto Hissopo – Sistema de Monitoramento Ambiental via IoT
Monitoramento de temperatura, umidade e qualidade do ar com ESP32, DHT22, MQ-135, LCD I2C e protocolo MQTT

📘 1. Descrição Geral do Projeto
O Hissopo é um sistema de monitoramento ambiental baseado em Internet das Coisas (IoT) capaz de medir temperatura, umidade e presença de gases tóxicos em ambientes internos.
O nome Hissopo foi escolhido por remeter simbolicamente à ideia de purificação, relacionando-se à proposta do projeto: detectar e alertar sobre potenciais riscos à qualidade do ar.
O protótipo utiliza o microcontrolador ESP32 conectado via Wi-Fi, publicando dados para um broker MQTT (Mosquitto). O sistema também conta com atuadores que emitem alertas imediatos:


LED vermelho — alerta visual


Buzzer ativo — alerta sonoro


O projeto foi desenvolvido no contexto acadêmico, contribuindo diretamente para o ODS 3 – Saúde e Bem-Estar, ao fornecer um meio acessível de monitoramento da qualidade do ar.

📘 2. Funcionamento e Uso (para quem quiser reproduzir)
🏗 Como o sistema funciona


O ESP32 lê:


temperatura e umidade (DHT22)


nível de gases (MQ-135)




Os dados são exibidos no display LCD I2C.


O ESP32 conecta-se ao Wi-Fi e envia os dados ao Mosquitto MQTT instalado em um computador.


Qualquer cliente MQTT pode visualizar:


hissopo/sensor/temperatura


hissopo/sensor/umidade


hissopo/sensor/gas




O usuário também pode enviar comandos para:


hissopo/atuador/led/set → ON/OFF


hissopo/atuador/buzzer/set → ON/OFF




Se as leituras ultrapassam limites seguros, o sistema aciona automaticamente:


LED


Buzzer


Mensagens são enviadas ao MQTT




▶️ Como rodar o projeto


Instale o Arduino IDE


Instale as bibliotecas do arquivo /codigo/bibliotecas.txt


Edite o arquivo credenciais-exemplo.h com o SSID/senha do Wi-Fi


Suba o código hissopo.ino para o ESP32


Instale o Mosquitto e rode o broker


Use MQTT Explorer para observar os dados e controlar o sistema



📘 3. Software Desenvolvido e Documentação de Código
O código-fonte completo está no diretório:
/codigo/hissopo.ino

A documentação de funções e módulos inclui:


setup() – inicialização de hardware, rede e MQTT


loop() – leitura de sensores, publicação de dados e exibição no LCD


callback() – recebe comandos para LED e buzzer


reconnect() – reconexão automática ao broker MQTT


Além disso, o diretório contém:


bibliotecas.txt — lista das bibliotecas usadas


credenciais-exemplo.h — modelo para suas credenciais



📘 4. Hardware Utilizado
🔌 Componentes Eletrônicos


ESP32 DOIT Devkit V1 (ESP-WROOM-32)


Sensor DHT22 (temperatura e umidade)


Sensor MQ-135 (qualidade do ar)


Display LCD 16x2 com I2C (PCF8574)


LED vermelho


Resistor 220 Ω para o LED


Buzzer Ativo


Protoboard


Jumpers (macho-macho, fêmea-macho, fêmea-fêmea)


Resistores: 10kΩ e 22kΩ (divisor de tensão para saída A0 do MQ-135)


Cabo USB para alimentar o ESP32


📐 Ligações e Diagrama
O diagrama completo encontra-se em:
/diagramas/

Incluindo:


Diagrama do hardware (Fritzing)


Fluxograma do funcionamento


Arquitetura da comunicação MQTT


Layout do protótipo montado



📘 5. Documentação das Interfaces, Protocolos e Comunicação
🌐 Interface TCP/IP
O ESP32 se conecta a uma rede Wi-Fi utilizando o protocolo TCP/IP para se comunicar com o broker MQTT.
📡 Protocolo MQTT
O projeto adota o protocolo MQTT, pela sua leveza e eficiência, ideal para IoT.
O ESP32:
Publica


hissopo/sensor/temperatura


hissopo/sensor/umidade


hissopo/sensor/gas


Assina


hissopo/atuador/led/set


hissopo/atuador/buzzer/set


Ao receber mensagens:


"ON" → ativa o atuador


"OFF" → desliga o LED ou o buzzer

Isso transforma o projeto em um sistema bidirecional, permitindo:

Monitoramento remoto

Controle remoto de atuadores

Reação automática a eventos críticos

📘 6. Resultados Obtidos

Durante os testes, o sistema apresentou funcionamento estável, permitindo monitoramento contínuo e envio de alertas automáticos.

Foram realizados testes com:

Fósforo/isqueiro → aumento abrupto no MQ-135

Vela acesa → aumento gradual de temperatura

Umidificador → alteração de umidade

Os atuadores responderam corretamente aos limites configurados.

📊 Tabela de Testes (valores fictícios – substitua pelos reais)
Nº Medição	Sensor/Ação	Tempo de Resposta (ms)
1	MQ-135 → MQTT	820 ms
2	MQ-135 → MQTT	910 ms
3	MQ-135 → MQTT	870 ms
4	MQ-135 → MQTT	890 ms
Média		872 ms
Nº Medição	Atuador (LED/Buzzer)	Tempo de Ação (ms)
1	LED ligado por MQTT	110 ms
2	LED ligado por MQTT	120 ms
3	Buzzer ON por MQTT	105 ms
4	Buzzer ON por MQTT	98 ms
Média		108 ms

Os gráficos correspondentes estão na pasta:

/resultados/

🎥 7. Vídeo-Demonstração

O vídeo apresentará:

Identificação da autora

Contexto do problema

Demonstração do protótipo

Testes com vela e fósforo

Funcionamento MQTT

Time-lapse da montagem

🔗 Link do vídeo (YouTube – não listado):
(insira aqui)

🗂 8. Repositório no GitHub

O repositório contém:

📁 /codigo
— Código completo hissopo.ino
— bibliotecas.txt com todas as dependências
— credenciais-exemplo.h para configuração

📁 /hardware
— Lista de componentes
— Esquema elétrico (Fritzing)
— Fotos da montagem

📁 /diagramas
— Diagrama MQTT
— Fluxograma do sistema
— Arquitetura geral

📁 /resultados
— Gráficos
— Capturas de tela do MQTT Explorer
— Tabela de testes

🔗 Link do repositório GitHub:
(insira aqui)

🧾 9. Conclusão

O Projeto Hissopo atinge completamente os objetivos propostos: realizar o monitoramento ambiental em tempo real, emitir alertas automáticos e integrar comunicação IoT via MQTT.

✔ Objetivos alcançados

Medição confiável de temperatura, umidade e gases

Exibição local (LCD) e remota (MQTT)

Comunicação bidirecional

Acionamento automático de atuadores

Baixa latência na transmissão de dados

✔ Dificuldades e soluções

O projeto começou com Blynk, mas foi necessário substituir pelo MQTT → resolvido com Mosquitto.

Faltavam jumpers e resistores → ajustes improvisados e compra de novos componentes.

A protoboard pequena dificultou a montagem → reestruturação do layout.

Ruídos no MQ-135 → aplicação de divisor de tensão correto.

LCD não exibia dados → ajuste do contraste e correção de endereço I2C.

✔ Vantagens

Baixo custo

Fácil reprodução

Alta compatibilidade com IoT

MQTT leve e confiável

Projeto modular e expansível

✔ Desvantagens

MQ-135 requer tempo de pré-aquecimento

Sensibilidade a interferências

Dependência da rede Wi-Fi

✔ Melhorias futuras

Dashboard web em Node-RED

Armazenamento histórico em banco de dados

Caixa impressa em 3D

Suporte a vários ambientes simultâneos

Integração com nuvem (AWS IoT / Azure / Google IoT)

📚 10. Referências

