#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#define pushButton D4
const int trigPin = 5;
const int echoPin = 4;
const int buzzer = 16;
const int ledPin = 16;
//const int pushButton = 2;

char auth[] = "E86F7W_d3h9qERaxfMQgOgVAceAPLlpb";
char ssid[] = "BSNL FIVER";
char pass[] = "M@hit1209";
#define BOTtoken "1453731462:AAERm1T46FN-BtiW2GiXhbCHJYLMBFJkfRk"  // your Bot Token (Get from Botfather)
#define CHAT_ID "@yashtheft"
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);



 
// defines variables
long duration;
int distance;
int safetyDistance;
 
 
void setup() {
   

  client.setInsecure();
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(pushButton, INPUT); 
pinMode(buzzer, OUTPUT);
pinMode(ledPin, OUTPUT);
Serial.begin(115200); // Starts the serial communication
Blynk.begin(auth, ssid, pass);
}
 
 
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
 
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
 
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
 
// Calculating the distance
distance= duration*0.034/2;
 
safetyDistance = distance;
if (safetyDistance <= 15){
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin, HIGH);
   bot.sendMessage(CHAT_ID, "Alert !! ghsakusllka", "");
  Serial.println("Keep safety distance please");
}
else{
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
}

 Blynk.run();
 
// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(distance);
int val = digitalRead(pushButton);
if(val == HIGH){
  Serial.print("pushbutton push: ");
  digitalWrite(ledPin, HIGH);
  bot.sendMessage(CHAT_ID, "Alert !!", "");
}
else{
  digitalWrite(ledPin, LOW);
}
}
