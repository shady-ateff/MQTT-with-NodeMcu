#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>  // MQTT Library

/*
  MQTT uses a Publisher Subscriber model :
    *One client publishes a message to a Topic* 
    The Broker(MQTT server) receives the message*
    The Broker then forwards the message to all clients subscribed to that Topic
*/

const char* ssid = "Orange_";         // WiFi SSID
const char* password = "orange1234";  // WiFi password

// Public MQTT Broker (can be replaced with a local broker IP)
const char* mqtt_server = "broker.hivemq.com";
const int mqttPort = 1883;

// Optional authentication (commented out)
const char* mqttUser = "MQTT_USERNAME";
const char* mqttPassword = "MQTT_PASSWORD";

WiFiClient espClient;            // Create a WiFi client"start a TCP with sever"
PubSubClient client(espClient);  // Create an MQTT client using the WiFi client

unsigned long lastMsg = 0;  // Timer control for periodic messages
char msg[50];               // Message buffer
int value = 0;              // Incremental value for message testing

const int ledPin = D4;  // LED pin definition

void setup() {
  Serial.begin(115200);                     // Start Serial Monitor
  pinMode(ledPin, OUTPUT);                  // Set LED pin as output
  setUpWIFI();                              // Connect to WiFi
  client.setServer(mqtt_server, mqttPort);  // Set MQTT Broker
  client.setCallback(callback);             // Set message received callback
}
void loop() {
  if (!client.connected()) {
    reconnect();  // Reconnect if MQTT client is disconnected
  }
  client.loop();  // Keep MQTT connection alive
  long now = millis();
  if (now - lastMsg > 5000) {  // Send a message every 5 seconds
    lastMsg = now;
    ++value;
    snprintf(msg, 50, "Hello from ESP! Count: %d", value);
    Serial.print("Publishing message: ");
    Serial.println(msg);
    client.publish("myhome/test", msg);  // Publish to topic
  }
}

// Connect to WiFi network
void setUpWIFI() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());  // Print local IP address
}

// Reconnect to MQTT Broker if disconnected
void reconnect() {
  // Public brokers disconnect inactive clients quickly, so reconnect as needed
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");


    // Generate a unique client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    // Try to connect using the random client ID
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("myhome/test");            // Subscribe to topic(s)
      client.publish("myhome/test", "i'm Here");  // Subscribe to topic(s)
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());  // Print error code
      Serial.println(" try again in 5 seconds");
      delay(5000);  // Wait before retrying
    }
  }
}

// Callback when a subscribed message is received
// Parameters:
//   - topic: topic name as c-string
//   - payload: byte array of the message
//   - length: length of the message
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);
  String recvMsg = "";

  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);  // Print message content
    recvMsg += (char)payload[i];
  }
  Serial.println();

  // 🔁 Add logic here to respond to specific messages

  if (recvMsg == "on") {
    digitalWrite(ledPin, LOW);  // Example: Turn off LED (for demo)
  }

  else if (recvMsg == "off") {
    digitalWrite(ledPin, HIGH);  // Example: Turn off LED (for demo)
  } else Serial.println(recvMsg);
}
