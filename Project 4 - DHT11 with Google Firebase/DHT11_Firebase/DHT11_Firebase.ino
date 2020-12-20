#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Set these to run example.
#define FIREBASE_HOST "https://dht11-firebase-eaf24-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "A4X6xvi1qlotPXsiMFAXDhc5nuoNVYj3pltrlWhN"
#define WIFI_SSID "MELTRADI"
#define WIFI_PASSWORD "redline212"

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin();
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  //Baca sensor suhu dan kelembaban
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  
  // set value
  Firebase.setFloat("suhu", t);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  Firebase.setFloat("kelembaban", h);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.println ("Data Suhu dan Kelembaban Sukses Terkirim");
  delay(1000);
}
