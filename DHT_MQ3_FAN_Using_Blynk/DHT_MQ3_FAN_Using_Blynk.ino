#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#define DHTPIN D2     // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   
   
#define FAN_PIN D6   // FAN RELAY
WidgetLED FAN(V0);

char auth[] = "q_URao70sxi2Z3B6Y5H0lnzE7RWgCBcD";
char ssid[] = "hack";
char pass[] = "Easy@2021";

float humDHT = 0;
float tempDHT = 0;
int Val=0;

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.print(" The Threshhold value is: ");
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  Blynk.begin( auth, ssid , pass );
}

BLYNK_WRITE(V3)
{
  Val = param.asInt(); // assigning incoming value from pin V3 to a variable

  Serial.print(" The Threshhold value is: ");
  Serial.println(Val);
  Serial.println();

}

void loop() {
  
  Blynk.run();

  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!

  humDHT = dht.readHumidity();
  // Read temperature as Celsius (the default)
  tempDHT = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humDHT) || isnan(tempDHT))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print(F("Temperature: "));
  Serial.print(tempDHT);
  Serial.print(F("°C "));
  Serial.println();
  Serial.print(F("Humidity: "));
  Serial.print(humDHT);
  Serial.print(F("%"));
  Serial.println();
  
  Serial.println("***********************");
  Serial.println();

  // Compare Threshold value from Blynk and DHT Temperature value.
  if (Val > tempDHT)
  {
    digitalWrite(FAN_PIN, HIGH);
    FAN.off();
}
  else {
    digitalWrite(FAN_PIN, LOW);
    FAN.on();
    
  } 

  Blynk.virtualWrite(V1, tempDHT);
  Blynk.virtualWrite(V2, humDHT);
}
