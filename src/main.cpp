#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <FS.h>

#define DHTPIN D7    // Pin, do którego podłączony jest czujnik DHT11 (D4 odpowiada GPIO2)
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

int czynnosc =0;
void setup() {
    Serial.begin(115200);
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }
    dht.begin();
    pinMode(D0,INPUT);
pinMode(D1,INPUT);
pinMode(D2,INPUT);

pinMode(D3, OUTPUT);
pinMode(D4, OUTPUT);
pinMode(D5, OUTPUT);
pinMode(D6, OUTPUT);
pinMode(D8, OUTPUT);

analogWrite(D3, 0);
analogWrite(D4, 0);
digitalWrite(D5, LOW);
digitalWrite(D6, LOW);
digitalWrite(D8, LOW);
}

void loop() {
    // Odczyt danych z czujnika
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Sprawdzenie, czy odczyt się powiódł
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Nie można odczytać danych z czujnika DHT11!");
        return;
    }

    // Wyświetlenie danych na serial monitorze
    Serial.print("Wilgotność: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" *C");

    // Zapis do pliku
    File file = SPIFFS.open("/dht11_data.txt", "a");
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }
    file.print("Wilgotność: ");
    file.print(humidity);
    file.print(" %, Temperatura: ");
    file.print(temperature);
    file.println(" *C");
    file.close();
     
  czynnosc =0;
if (digitalRead(D0)==LOW)
{
 czynnosc =1;
}
if (digitalRead(D1)==LOW)
{
  czynnosc =2;
}
if (digitalRead(D2)==LOW)
{
czynnosc =3;
}
switch (czynnosc)
{
  case 1:
  analogWrite(D3, 10);
  analogWrite(D4, 1000);
  delay(250);
  analogWrite(D3, 0);
  analogWrite(D4, 0);
  break;

  case 2:
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  delay(250);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  break;

  case 3:
  digitalWrite(D8, HIGH);
  delay(250);
  digitalWrite(D8,LOW);
  break;

  default:
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D8, LOW);
  break;
}
   // delay(2000); // Opóźnienie przed kolejnym odczytem
}
