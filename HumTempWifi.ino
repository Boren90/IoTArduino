#include <WiFiS3.h>
#include "settings.h"


char ssid[] = SECRET_SSID;
char password[] = SECRET_PASSWORD;

void setup() {
  Serial.begin(9600);

  Serial.println("Ansluter till WIFI...");


  int status = WiFi.begin(ssid, password);

  while (status != WL_CONNECTED) {
    delay(1000);
    status = WiFi.status();
  }

  Serial.println("SSID: ");
  Serial.println(WiFi.SSID());
  delay(2000);//sätter en delay för att vänta in localIP
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Adress: ");
  Serial.println(ip);

}

void loop() {

}