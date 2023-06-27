
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(D4, DHT11); //(sensor pin,sensor type)

char auth[] = ""; //Enter the Auth code which was send by Blink
char ssid[] = "";  //Enter your WIFI Name
char pass[] = "";  //Enter your WIFI Password

BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("Humi : ");
  lcd.print(h);

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}
void setup() {

  Wire.begin(D2, D1);
//  lcd.init();
  lcd.backlight();
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(100L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
