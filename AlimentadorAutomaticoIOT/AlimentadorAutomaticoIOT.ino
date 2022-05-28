#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <Servo.h>
#include <PubSubClient.h> //inclui suporte ao MQTT no HiveMQ Cloud

const char* ssid     = "******";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "******";     // The password of the Wi-Fi network

const char* mqtt_server = "broker.mqttdashboard.com"; //URL do broker MQTT
const int mqtt_server_port = 1883; //porta do broker MQTT

#define MSG_BUFFER_SIZE (500) //define MSG_BUFFER_SIZE como 500
#define pinoServo D0
#define pinPIR D1
WiFiClient client; //cria o objeto client
PubSubClient mqtt_client(client); //cria o objeto mqtt_client
Servo s; //OBJETO DO TIPO SERVO
long lastMsg = 0;

String clientID = "clienteid"; //identificacao do cliente

String topicoPrefixo = "MACK12029139"; //para o prefixo do topico, utilizar MACK seguido do TIA
String topicoTodos = topicoPrefixo + "/#"; //para retornar todos os topicos
String topico_0 = topicoPrefixo + "/hello"; //topico para teste
String mensagem_0 = "NodeMCU Connected"; //mensagem para o topico 0
String topico_1 = topicoPrefixo + "/sensorPIR"; //topico para o sensor 1
String mensagem_1 = ""; //mensagem para o topico 1
String topico_2 = topicoPrefixo + "/servoMotor"; //topico para o atuador 1
String mensagem_2 = ""; //mensagem para o topico 2
String mensagemTemp = ""; //armazena temporariamente as mensagens recebidas via MQTT


void setup_wifi() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

// Funcao para receber mensagens
void callback(char* topic, byte* payload, unsigned int length) {
  mensagemTemp = "";
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    mensagemTemp += (char)payload[i];
  }

  if (String(topic) == topico_2) {
    mensagem_2 = mensagemTemp;
  }

  Serial.println();
}

// Funcao para conectar no broker MQTT
void reconnect() {
  // Loop until we’re reconnected
  while (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection…");

  // Create a random client ID
    randomSeed(micros()); //inicializa a semente do gerador de numeros aleatorios
    clientID += String(random(0xffff), HEX);

  // Attempt to connect
    if (mqtt_client.connect(clientID.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqtt_client.publish(topico_0.c_str(), mensagem_0.c_str());
      // ... and resubscribe
      mqtt_client.subscribe(topicoTodos.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
} 

void setup() {
  s.attach(pinoServo);
  s.write(0);
  pinMode(pinPIR, INPUT);
  Serial.begin(9600); //inicializa a saida serial

  setup_wifi();

  mqtt_client.setServer(mqtt_server, mqtt_server_port); //configura a conexao com o broker MQTT
  mqtt_client.setCallback(callback); //configura o recebimento de mensagens
}

void loop() { 
  if (!mqtt_client.connected()) {
    reconnect();
  }
  mqtt_client.loop(); //processa as mensagens e mantem a conexao com o broker MQTT

  bool valorPIR = digitalRead(pinPIR);

  if (valorPIR) {
     mensagem_1 = "UM MOVIMENTO FOI DETECTADO";
     mensagem_2 = "Sevor Motor foi movido a 180º graus!";
     mqtt_client.publish(topico_1.c_str(), mensagem_1.c_str());
     mqtt_client.publish(topico_2.c_str(), mensagem_2.c_str());
     s.write(180);
     delay(1500);
     s.write(0);
     delay(30000000);
  }
  }
