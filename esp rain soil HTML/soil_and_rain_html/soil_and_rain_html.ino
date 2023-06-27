*****************************************************
 * Date: 1 july 2018
 * Written by: Usman Ali Butt
 * Property off: microcontroller-project.com
 * ***************************************************/
#include <ESP8266WiFi.h>
 
const char* ssid = "Your SSID";
const char* password = "Your Wifi Password";
 
int Raw       = A0;      //Analog channel A0 as used to measure temperature
int threshold = 13;      //Nodemcu digital pin water sensor read
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  // Connect to WiFi network
  pinMode(threshold,INPUT_PULLUP); //Pin#13 as output-Activate pullup at pin 13
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);     //Begin WiFi
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address on serial monitor
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");    //URL IP to be typed in mobile/desktop browser
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  float percentage = 0.0;
  int value = LOW;
  if (request.indexOf("/Up=ON") != -1)  {
      //Analog pin reading output voltage by water moisture rain sensor
       float reading = analogRead(Raw);     
       percentage = (reading/1024) * 100;   //Converting the raw value in percentage
    value = HIGH;
  }

 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1 align=center>Rain Soil Water moisture Level</h1><br><br>");
  client.print("Moisture Level Percentage =");
  client.print(percentage);
  client.print("%");
  client.println();

if(digitalRead(threshold)==HIGH){
  client.println("Threshold Reached = Rain detected / Moisture exceeded / Water detected");
  }
 
  if(value == HIGH) {
    client.println("Updated");
  } else {
    client.print("Not Updated");
  }
  client.println("<br><br>");
  client.println("<a href=\"/Up=ON\"\"><button>Update Moisture Level</button></a><br />");  
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
