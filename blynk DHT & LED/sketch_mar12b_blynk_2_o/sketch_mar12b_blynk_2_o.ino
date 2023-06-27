
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

char auth[] = "ZcEqnyTPwFyIGNR6FvePkuQ6FKNvq_Uf";
char ssid[] = "hac";
char pass[] = "hac123456";

#define DHTPIN D1 //--> DHT11 sensor output is connected to PIN D1 on NodeMCU   
#define DHTTYPE DHT11 //--> DHT sensor type declaration     
DHT dht(DHTPIN, DHTTYPE);  

#define FAN_PIN D6


BlynkTimer timer; 
void sendDHT11SensorVal() {
  int h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read data from DHT sensor!");
    delay(500);
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("% | Temperature: "));
  Serial.print(t);
  Serial.println(F("°C"));
  String Hum = String(h);
  String Tem = String(t);
  Blynk.virtualWrite(V0, Hum);
  Blynk.virtualWrite(V1, Tem);
} 
void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass); 
  dht.begin(); //--> Starting the DHT11 library
  timer.setInterval(5000L, sendDHT11SensorVal);
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
 
}

void loop()
{
  Blynk.run();
  timer.run();

   if (21 > Tem)
  {
    digitalWrite(FAN_PIN, HIGH);
    
   }
  else {
    digitalWrite(FAN_PIN, LOW);
    
  } 

}
