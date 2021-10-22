#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <BlynkSimpleEsp8266.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>


const int trigPin = 5;  // D1 (for trig pin of HC-SRO4)
const int echoPin = 4;  // D2 (for echo pin of HC-SRO4)
const int buzzer = 16;  // D0 (for Obstacle LED ALARM)
const int ledPin = 16;  // D0 (for Obstacle BUZZER ALARM)
const int ledWater = 12;  // D6 (for Water Alarm)
const int inputPin = 2;// D4 pin (for SOS Pushbutton) 
const int ledSOS=13; // D7 pin (for SOS LED)
int val = 0; // variable for reading the pin status


char auth[] = "E86F7W_d3h9qERaxfMQgOgVAceAPLlpb";   // Authetication code of Blynk
char ssid[] = "BSNL FIVER";  // WiFi name
char pass[] = "M@hit1209";   // Wifi Password
#define BOTtoken "1453731462:AAERm1T46FN-BtiW2GiXhbCHJYLMBFJkfRk"  // your Bot Token (Get from Botfather)
#define CHAT_ID "@yashtheft"  // Telegram chat id 
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
pinMode(buzzer, OUTPUT); // Sets the buzzer as Output
pinMode(ledPin, OUTPUT); // Sets ledPin as Output
pinMode(ledWater, OUTPUT); //Sets ledWater as Output
Serial.begin(115200); // Starts the serial communication
pinMode(inputPin, INPUT); // set pusbutton as input
pinMode(ledSOS, OUTPUT);  // set ledSOS as Output
client.setInsecure();
WiFi.begin(ssid, pass);
Blynk.begin(auth, ssid, pass);
}
 
 
void loop() {
// WATER ALARM SYSTEM  
digitalWrite(ledWater, HIGH);

//ROAD CROSSING MODE
 Blynk.run();

//OBSTACLE ALARM

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
  delay(500);
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
  Serial.println("Keep safety distance please");
}
else{
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
}
//Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);


val = digitalRead(inputPin); // read input value 
   Serial.println(val);     //Printing val value in Serial Monitor
   if (val == HIGH)
   { 
      bot.sendMessage(CHAT_ID, "Your Dear one, stuck in a problem!!! Requested you for help. Please contact him ASAP.!", "");
      digitalWrite(ledSOS, HIGH);
      delay(500);
      digitalWrite(ledSOS, LOW);
      delay(500);
   }  

   delay(50);
}
