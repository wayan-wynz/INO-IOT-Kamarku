#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "DHT.h"
#define DHTPIN D5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

char ssid[] = "MUTIARA 3";
char password[] = "10807007";
//char server[] = "192.168.1.7";

//char server[] = "192.168.1.4";
//domain hosting nya
char server[] = "iot-sensorr.my.id";

const int ledPin =  LED_BUILTIN;
#define pinLED 4
#define relay D3

void setup() 
{
  Serial.begin(115200);
  dht.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(relay, OUTPUT);
  
  //WiFi.hostname("NodeMCU");
  WiFi.begin(ssid, password);
  Serial.println("Conneecting...");
  
  while(WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(ledPin, HIGH);
    digitalWrite(pinLED, LOW);
    digitalWrite(relay, LOW);
    Serial.print(".");
    delay(1000);
  }
  digitalWrite(ledPin, LOW);
  digitalWrite(pinLED, HIGH);
  digitalWrite(relay, HIGH);
  Serial.println("Terhubung !!");
}

void loop() 
{
  float temp = dht.readTemperature();
  int hum = dht.readHumidity();
  
  Serial.println("Suhu :" + String(temp));
  Serial.println("Keembaban :" + String(hum));
  
  //pengiriman data sensor
  WiFiClient wClient;
  //cek koneksi ke web server
  const int httpPort = 80;
  if(!wClient.connect(server, httpPort))
  {
    Serial.println("Gagal koneksi ke Server");
    return;
  }
  //proses pengiriman data ketika terkoneksi ke server
  String url;
  HTTPClient http;
//menuju website laravel
//  url = "http://" + String(server) + "/laravelsensor/public/simpan/" + String(temp) + "/" + String(hum);

//menuju website native
//  url = "http://" + String(server) + "/sensor-iot/kirimdata.php?suhu=" + String(temp) + "&kelembaban=" + String(hum);
  
  //apabila sudah di hosting maka gunakan yang di bawah
  url = "http://" + String(server) + "/config/kirimdata.php?suhu=" + String(temp) + "&kelembaban=" + String(hum);
//  "http://" + String(serverhosting) + "/config/kirimdata.php?suhu=" + String(tem) + "&kelembaban=" + String(hum);
  
  //eksekusi url
  http.begin(wClient, url);
  http.GET();
  String respon = http.getString();
  Serial.println(respon);
  http.end();
  delay(10000);
}
