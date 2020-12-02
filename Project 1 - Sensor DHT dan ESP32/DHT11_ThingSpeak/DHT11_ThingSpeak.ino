#include "ThingSpeak.h"
#include "DHT.h"
#include <SPI.h>
#include <WiFi.h>

#define DHTPIN 4
#define DHTTYPE DHT11  // DHT 22  (AM2302), AM2321

char ssid[] = "MELTRADI";
char pass[] = "redline212";

unsigned long myChannelNumber = 1245022;
const char* myWriteAPIKey = "PNITFO8N9N66XPML";

int keyIndex = 0;
WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop() {
  // Menghubungkan ke internet
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  //Mencoba untuk menghubungkan ke internet
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();
  
  // Mengirim data ke thingspeak
  ThingSpeak.setField(1, suhu);
  ThingSpeak.setField(2, kelembaban);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Berhasl update ke thingspeak");
    Serial.print("Suhu : ");
    Serial.println(suhu);
    Serial.print("Kelembaban : ");
    Serial.println(kelembaban);
  }
  else{
    Serial.println("Gagal update. HTTP error code " + String(x));
  }
  delay(15000); // Tunggu 15 detik untuk update lagi ke Thingspeak
}
