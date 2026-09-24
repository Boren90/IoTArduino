#include <WiFiS3.h>
#include "settings.h"
#include "DHT.h"

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

char ssid[] = SECRET_SSID;
char password[] = SECRET_PASSWORD;

WiFiServer server(80);

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
  delay(2000);  //sätter en delay för att vänta in localIP
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Adress: ");
  Serial.println(ip);

  server.begin();

  dht.begin();

  Serial.println("DHT11 startar...");
}

void loop() {

  WiFiClient client = server.available();  //När client är ansluten lagras han i objektet client
  //Client är false så länge det inte är någon uppkopplad emot oss
  if (client) {
    Serial.println("Ny klient ansluten");
    String request = client.readStringUntil('\r');// läser inkommande paket tills dess att det är slut
    Serial.println(request);

    client.stop();  //Går ur loopen för annars kommer sidan bara stå och ladda.
    Serial.println("Klient har kopplat från.");
  }

  delay(500);

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