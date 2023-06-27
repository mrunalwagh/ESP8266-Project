
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[ ] = "1nid25C7q7kB_Du5Qw-i5ZK6SC1afulw";

char ssid[ ] = "hack";
char pass[ ] = "Easy@2021";


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(6, INPUT);
 
}

void loop()
{
   if (0 == digitalRead(6)) 
   {
  Serial.println("SIGNAL HIGH");
  Blynk.notify("Trigger");
  }
  if (1 == digitalRead(6)) {
  Serial.println("SIGNAL LOW");
}
  delay(1000);
  Blynk.run();
}
