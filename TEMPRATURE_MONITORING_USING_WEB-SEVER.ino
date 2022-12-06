#include<ESP8266WiFi.h>
const char* ssid="tanu";
const char* password = "taniksha";
int sensorPin=A0;
WiFiServer server(80);
void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print("connecting to");
  Serial.print(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
   delay(50);
   Serial.print(".");
   
  }
  Serial.println("WIFI CONNECTED");
  server.begin();
  Serial.println("SERVER STARTED");
  Serial.print("use this URL to connect");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
}


void loop() {
  int analogValue=analogRead(sensorPin);
  float millivolts=(analogValue/1024.0)*3300;
  float celcius=millivolts/10;
  Serial.print("In degree C=");
  Serial.print(celcius);
  float fahreheit=((celcius*9)/5+32);
  Serial.println("in Fahreheit=");
  Serial.println(fahreheit);
  delay(1000);

  WiFiClient client=server.available();
  if(!client)
  {
    return;
  }
  Serial.println("new client");
  while(!client.available())

  {
    delay(0.5);
  }
  String request=client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  int value=LOW;
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type:text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<br><br>");
  client.println("<center>");
  client.print("<h3>Temperature in C=</h3>");
  client.println("<meta http-equiv='refresh' content='1'>");
  client.println(celcius);
  
  client.println("<br><br>");
  client.println("<h3>Temperature in F= ");
  client.println("<meta http-equiv='refresh' content='1'>");
  client.println(fahreheit);
  client.println("</html>");
  delay(1);
  Serial.println("Client disconnected");
  Serial.print("");
  }
