#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "YiUN8hAkxNK5Fbx7vNjHqSn7aZURmCwN";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hac";
char pass[] = "hac123456";

#include <Wire.h> // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include <HX711.h>

// Capteur de poids setting
const int SCALE_DOUT_PIN =D5;
const int SCALE_SCK_PIN =D6;
HX711 scale(SCALE_DOUT_PIN, SCALE_SCK_PIN);
int analogPin = A0;
int moisture;
int percentage;

int map_low = 686;
int map_high = 350;

float weight;
float weightCorrection = -8.55 ; // The weight of the hive to be removed from the result orignal= 3.98


void getWeight()
{
  //String weight = String(scale.get_units(1), 2);
  weight = scale.get_units(1);
  weight = -((weight+weightCorrection)/3); // The new line, which deducts the correction value from the reading
  Serial.print("Weight = ");  
  Serial.println(weight);
 
}


void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);//starts wifi and Blynk
  Serial.println("Connected to Blynk");
  scale.set_scale(-6000/0.128);
  //scale.tare();
}


void loop()
{
  delay(4000);
  getWeight();
 
  Blynk.virtualWrite(V4, weight);
  Blynk.virtualWrite(V7,percentage);
 
  Serial.println(" seconds");
  Blynk.run(); // Needed to ensure that the Wake Time value is always uploaded to Blynk before going to sleep
  delay(100);
  moisture = analogRead(analogPin);
  Serial.print("Raw: ");
  Serial.print(moisture);

  percentage = map(moisture, map_low, map_high, 0, 100);

  Serial.print(" | Percentage: ");
  Serial.print(percentage);

  Serial.println("%");

  delay(1000);
}
