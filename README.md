# IoT Sensor-projekt - Arduino

Detta projekt använder en Arduino UNO R4 WiFi och en DHT11-sensor för att mäta temperatur och luftfuktighet.

Mätdata skickas sedan via WiFi till en lokal server genom ett REST API.

## Exempel på användning av applikationen

**Problem:** En husägare har ett garage eller förråd där temperatur och luftfuktighet kan variera mycket. Det kan vara svårt att veta hur klimatet faktiskt har sett ut över tid och om åtgärder behöver vidtas.

**Lösning:** Med denna applikation kan användaren övervaka temperatur och luftfuktighet över tid och upptäcka förändringar i klimatet.

## Hårdvara som behövs

- Arduino UNO R4 WiFi
- DHT11 temperatur- och luftfuktighetssensor
- USB-kabel för installation och överföring av mjukvara
- Breadboard och kopplingskablar, alternativt lödning av sensorn direkt på kablarna


## Dataflöde

### Arduino

Arduino läser av:

- Temperatur i °C
- Luftfuktighet i %

### WiFi

- Mätdata skickas som JSON via REST API till backend.

### Spring Boot Backend

- Tar emot och hanterar data.
- Lagrar mätningarna i en lokal MongoDB-databas.

### Frontend

- Hämtar data från backend via REST API.
- Visar mätningarna för användaren.
- Visar statistik och diagram för valda dagar.

## Installation

- Installera Arduino IDE.
- Installera stöd för Arduino UNO R4 WiFi.
- Installera de bibliotek som används av projektet.
- Klona repot.
- Skapa `settings.h` utifrån `settings.example.h`.
- Ange WiFi-namn och lösenord i `settings.h`.
- Öppna `HumTempWifi.ino` i Arduino IDE.
- Välj Arduino UNO R4 WiFi som board.
- Välj rätt COM-port.
- Ladda upp programmet till Arduino.

### Ange serverns IP-adress

Innan programmet laddas upp behöver serverns lokala IP-adress anges i Arduino-koden.

Exempel:

```cpp
char serverAdress[] = "192.168.0.12";
```