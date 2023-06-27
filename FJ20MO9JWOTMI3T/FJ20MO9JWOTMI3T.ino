#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "wE_6ldUPR-InfxI3_ok9QOYrjv7bYU8W";
char ssid[] = "hack";
char pass[] = "Easy@2021";
#define PIN_UPTIME V6
#define FAN_PIN D6
BLYNK_READ(PIN_UPTIME)
{
  Blynk.virtualWrite(PIN_UPTIME, millis() / 1000);
}

BlynkTimer timer;

void myTimerEvent()
{
  int analogValue = analogRead(A0); //reading the sensor on A0
  float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU   
  float celsius = millivolts/10;
  Blynk.virtualWrite(V0, celsius-10);
  Serial.println(celsius-10);
  
  if ((celsius-10) >21)
  {
    digitalWrite(D6, HIGH);
    Serial.println("Fan On");
  }
  else 
  {
    digitalWrite(D6, LOW);
    Serial.println("Fan Off");
  }
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  pinMode(FAN_PIN, OUTPUT);
}

void loop()
{
  
  Blynk.run();
  timer.run(); 
}
