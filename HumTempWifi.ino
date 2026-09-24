#include <WiFiS3.h>
#include "settings.h"
#include "DHT.h"

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

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
  delay(1000);  //sätter en delay för att vänta in localIP
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Adress: ");
  Serial.println(ip);

  dht.begin();

  Serial.println("DHT11 startar...");
}

void loop() {

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Kunde inte läsa från DHT11!");
    return;
  }

  Serial.print("Temperatur: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Luftfuktighet: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.println("--------------------");
  delay(5000);
}