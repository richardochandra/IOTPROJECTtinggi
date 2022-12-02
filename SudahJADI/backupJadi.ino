#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MQTTPubSubClient.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
// WiFi
const char *ssid = "AKUITA LT 2"; // Enter your WiFi name
const char *password = "Jogpa003";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "192.168.0.101";
const char *topicNama = "deiotchan/nama";
const char *topicHeight = "deiotchan/saveheight";
const char *topicSimpan = "deiotchan/triggerSimpan";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

const int trigPin = 12;
const int echoPin = 14;
const int jarakAwal = 73;
float duration, distance;
String namaa;



WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{

   pinMode(trigPin, OUTPUT); 
   pinMode(echoPin, INPUT); 
   Serial.begin(9600);
  // Robojax code for LCD with I2C
  // initialize the LCD, 
  lcd.begin();
 
  // Turn on the blacklight and print a message.
  lcd.backlight();
  // Robojax code for LCD with I2C

  //CONNECT MQTT
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("Broker anda sudah terkoneksi !!!");
          client.publish(topicNama,"Masukkan Nama :");
      } else {
          Serial.print("failed with state ");
          Serial.println(client.state());
          delay(2000);
      }
  }
  // publish and subscribe
  client.subscribe(topicNama);
  client.subscribe(topicSimpan);
//  client.publish(topicNama);

//for (int i = 0; i < 3; i++) {
//
//  lcd.clear();
//  lcd.setCursor (3,0);
//  lcd.print("W");
//  delay(200);
//  lcd.setCursor (4,0);
//  lcd.print("E");  
//  delay(200);
//  lcd.setCursor (5,0);
//  lcd.print("L");
//  delay(200);
//  lcd.setCursor (6,0);
//  lcd.print("L");
//  delay(200);
//  lcd.setCursor (7,0);
//  lcd.print("C");
//  lcd.setCursor (8,0);
//  delay(200);
//  lcd.print("O");
//  lcd.setCursor (9,0);
//  delay(200);
//  lcd.print("M");
//  lcd.setCursor (10,0);
//  delay(200);
//  lcd.print("E");
//  lcd.setCursor (11,0);
//  delay(200);
//  lcd.print("!");
//  lcd.setCursor (12,0);
//  delay(200);
//  lcd.print("!");
//  lcd.setCursor (13,0);
//  delay(200);
//
//  lcd.setCursor(2,1);
//  lcd.print("D");
//  delay(200);
//  lcd.setCursor(3,1);
//  lcd.print("e");
//  delay(200);
//  lcd.setCursor(4,1);
//  lcd.print("I");
//  delay(200);
//  lcd.setCursor(5,1);
//  lcd.print("o");
//  delay(200);
//  lcd.setCursor(6,1);
//  lcd.print("T");
//  delay(200);
//  lcd.setCursor(7,1);
//  lcd.print("C");
//  delay(200);
//  lcd.setCursor(8,1);
//  lcd.print("h");
//  delay(200);
//  lcd.setCursor(9,1);
//  lcd.print("a");
//  delay(200);
//  lcd.setCursor(10,1);
//  lcd.print("n");
//  delay(200);
//  lcd.setCursor(11,1);
//  lcd.print("^");
//  delay(200);
//  lcd.setCursor(12,1);
//  lcd.print("_");
//  delay(200);
//  lcd.setCursor(13,1);
//  lcd.print("^");
//  delay(200);
//  
// lcd.clear();
//}
}

// callback

void callback(char *topic, byte *payload, unsigned int length) {
    if (strcmp(topic,"deiotchan/nama")==0){
      namaa = "";
      Serial.print("Message arrived in topic: ");
      Serial.println(topicNama);
      Serial.print("Message:");
      for (int i = 0; i < length; i++) {
          namaa += (char)payload[i];
         
      }
      Serial.println(namaa);
      Serial.println("-----------------------"); 
    }
    if (strcmp(topic,"deiotchan/triggerSimpan")==0){
      float copyDistance = distance;
      char result[7];
      dtostrf(copyDistance,5,2,result);
      client.publish(topicHeight,result);
      Serial.println(copyDistance);
    }
}
 

void loop()
{
  client.loop();
  digitalWrite(trigPin, LOW); 
   delayMicroseconds(2); 
   digitalWrite(trigPin, HIGH); 
   delayMicroseconds(10); 
   digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distance = (duration*.0343)/2;
  
  //start of loop Robojax code for LCD with I2C
  lcd.clear();
  lcd.print("Nama  :");
  lcd.print(namaa);
  lcd.setCursor (0,1); // go to start of 2nd line
  lcd.print("Tinggi:");
  lcd.print(distance);
  lcd.print(" cm");

  //lcd.print(millis() / 1000);
  delay(500);
 //end of loopcode Robojax code for LCD with I2C
}
