#include <WiFiS3.h>
#include "settings.h"
#include "DHT.h"
#include <ArduinoHttpClient.h>

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

char ssid[] = SECRET_SSID;
char password[] = SECRET_PASSWORD;

char serverAdress [] = "192.168.0.12";
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

  // Läs av sensorn först
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Kontrollera att sensorn gav giltiga värden
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Kunde inte läsa från DHT11!");
    delay(2000);
    return;
  }

  // Skapa JSON från sensorvärdena
  String postData = "{\"humidity\":" + String(humidity) + ",\"temperature\":" + String(temperature) + "}";

  Serial.println("Skickar vår POST");
  Serial.println(postData);

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
  Serial.println(response);
  //10min
  delay(600000);
}