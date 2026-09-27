#include <WiFiS3.h>
#include "settings.h"
#include "DHT.h"
#include <ArduinoHttpClient.h>

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

char ssid[] = SECRET_SSID;
char password[] = SECRET_PASSWORD;

// char serverAdress [] = "192.168.0.12";
char serverAdress [] = "192.168.50.100";
int port = 8080;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAdress, port);

void setup() {
  //Startar Serial monitor
  Serial.begin(9600);

  Serial.println("Ansluter till WIFI...");

  int status = WiFi.begin(ssid, password);

  while (status != WL_CONNECTED) {
    delay(1000);
    status = WiFi.status();
  }
  Serial.println("Ansluten till WiFi");
  Serial.println("SSID: ");
  Serial.println(WiFi.SSID());
  delay(2000);  //sätter en delay för att vänta in localIP
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Adress: ");
  Serial.println(ip);

  dht.begin();

  Serial.println("DHT11 startar...");
}

void loop() {

  // String postData = "{\"humidity\":23.3}";
  String postData = "{\"humidity\":23.3,\"temperature\":21.7}";
  // String postData = "{\"humidity\":\"25\"}";

  Serial.println("Skickar vår POST");

  client.beginRequest();
  client.post("/api/humidity-temperature");

  client.sendHeader("Content-Type", "application/json");
  client.sendHeader("Content-Length", postData.length());

  client.beginBody();
  client.print(postData);
  client.endRequest();

  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.print(response);
  
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Kunde inte läsa från DHT11!");
    return;
  }
  // delay(2000);
  // Serial.print("Temperatur: ");
  // Serial.print(temperature);
  // Serial.println(" °C");

  // Serial.print("Luftfuktighet: ");
  // Serial.print(humidity);
  // Serial.println(" %");

  // Serial.println("--------------------");
}