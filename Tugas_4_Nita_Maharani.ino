//Library yang dibutuhkan
#include <ESP8266WiFi.h>
#include <DHT.h>
#include "FirebaseESP8266.h"

//Mendefinisikan pin dan tipe sensor DHT
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht11(DHTPIN, DHTTYPE);

//Isikan sesuai pada Firebase
#define FIREBASE_HOST "tugas-4-c48ca-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "0AmoBeDGGaMUjJnec3bJ5DSW6UesmW3uQAI2Nm9D"

//Nama Wifi
#define WIFI_SSID "Nita"
#define WIFI_PASSWORD "nita2110"

// Mendeklarasikan objek data dari FirebaseESP8266
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  dht11.begin();

  // Koneksi ke Wifi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connected");
  while (WiFi.status() !=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected with IP:");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 }

 void loop(){

  //Sensor DHT11 membaca suhu dan kelembaban
  float t = dht11.readTemperature();
  float h = dht11.readHumidity();

  // Memeriksa apakah sensor berhasil membaca suhu dan kelembaban
  if (isnan(t) || isnan(h)){
    Serial.println("Gagal membaca sensor DHT 11");
    delay(1000);
    return;
  }

  // Menampilkan suhu dan kelembaban kepada serial monitor
  Serial.print("Suhu : ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.print("Kelembaban : ");
  Serial.print(h);
  Serial.println(" %");
  Serial.println();

  //Memberikan status suhu dan kelembaban kepada firebase
  if(Firebase.setFloat(firebaseData,"/Hasil_Suhu/Suhu", t)){
    Serial.println("suhu terkirim");
  }else{
    Serial.println("suhu tidak terkirim");
    Serial.println("karena : "+firebaseData.errorReason());
  }

   if(Firebase.setFloat(firebaseData,"/Hasil_Kelembaban/kelembaban", h)){
    Serial.println("kelembaban terkirim");
  }else{
    Serial.println("kelembaban tidak terkirim");
    Serial.println("karena : "+firebaseData.errorReason());
  }
  delay(100);
}
