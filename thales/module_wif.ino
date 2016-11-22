// This is a Wi-Fi sketch that simply get on Serial a length
// and send the associated content via Wi-Fi.
/*
#include <ESP8266WiFi.h>

// Wi-Fi info
const char* ssid     = ".wifi-secret";
const char* password = "hacker2017";
// Server info
const char* host = "192.168.43.54";
const int httpPort = 8000;
 
void setup() {
  Serial.begin(115200);
  delay(100);
 
  // We start by connecting to a WiFi network  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
 
void send_picture() {
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    return;
  }
  
  while (Serial.available() <= 0)
    continue;
  // Get size
  String str = Serial.readStringUntil('\n');
  int len = str.toInt();
  
  int m_size = 2048;
  char message[m_size];
  while (Serial.available() <= 0)
    continue;
  // Send content of Serial for len bytes
  while (len)
  {
    int readed = Serial.readBytes(message, m_size);
    client.write(message, readed);
    len -= readed;
  }
  delay(500);
  
  client.flush();
  client.stop();
}

void loop()
{
  if (Serial.available() > 0)
    send_picture();
}
*/
