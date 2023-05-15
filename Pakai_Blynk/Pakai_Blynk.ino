#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266Ping.h>

char ssid[] = "EIGRP_Routing-TL";
char pass[] = "1234567890";
//char ssid[] = "Kost caca cia";
//char pass[] = "1122334455";
//char ssid[] = "Eigrp_Routingx";
//char pass[] = "1122334455";

//char ssid[] = "MUTIARA 3";
//char pass[] = "10807007";
//char ssid[] = "Ezcavalent_";
//char pass[] = "1234567890";

//char serverhosting[] = "192.168.1.4";
char serverhosting[] = "iot-sensorr.my.id";
//domain hosting nya
//char serverhosting[] = "iot-sensorr.000webhostapp.com";
//char serverhosting[] = "iot-sensors.rf.gd";
//char serverhosting[] = "iot-sensorr.byethost13.com"; 

//variabel array untuk data parsing TRIM
String arrData[3];


// Untuk IP Static
//IPAddress local_IP(192,168,1,18);
//IPAddress gateway(192,168,1,1);
//IPAddress subnet(255,255,255,0);
//IPAddress primaryDNS(8,8,8,8);
//IPAddress secondaryDNS(8,8,4,4);

char auth[] = "uiSLT8D-STXry3bYPYmDL_12yeiblrpN"; //token bylnk iot.serangkota.go.id
//char auth[] = "T1oBvUfz7-gctCwbCNxn7KlqAV7l2z4y"; //token bylnk developer asli
//char auth[] = "mrx-koIrie94v6KjcGWnmKvfyKgpiVWF"; //token bylnk server indo (103.56.206.108)

#include <ArduinoJson.h> // V6!
#include <BlynkSimpleEsp8266.h>
#include <WiFiClientSecure.h>
#define LED_PIN 4 //pin D2 di NodeMcu
#define ldrPin A0
#define relay D3

#include <YoutubeApi.h>
#define API_KEY "AIzaSyAua1Q2EUk51k1_x2vN0ZYw5WRnpHA6H5A"  //google apps API Token
#define CHANNEL_ID "UCXDmiL3ondYpFGJUAgGqdwA" // url ID channel
WiFiClientSecure client;
YoutubeApi api(API_KEY, client);
unsigned long timeBetweenRequests = 10000;
unsigned long nextRunTime;
long subs = 0;

//#include "CTBot.h";
//CTBot botku;
//String token = "5275213592:AAHh9nqDNoCCUgPU-ilsbfAxtoXr0oSENOc";
//const int id = 1320286853;

#define FASTLED_ESP8266_RAW_PIN_ORDER
#include "FastLED.h"
#define NUM_LEDS1 11
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define PIN1 D1
CRGB leds1[NUM_LEDS1];
int data=255;
int r,g,b;

#include <DHT.h>
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

//#if ESP8266
//#include <ESP8266HTTPClient.h>
//#include <ESP8266WiFi.h> 
////#define OLED_RESET     D4
//#endif

const String ducoUser = "wayan_wynz"; // Change this to your Duino-Coin username
const String ducoReportJsonUrl = "https://server.duinocoin.com/v2/users/" + ducoUser + "?limit=1";
//const int run_in_ms = 5000;

//const int MillisInfoDevice = 60000;
//const int MillisLED = 500;

const int ledPin =  LED_BUILTIN;

WidgetLCD lcd(V5);
WidgetTerminal terminalDuco(V10);
WidgetTerminal terminal_device(V11);
//WidgetTerminal terminal_hosting(V26);

//Ping ke google
const char* remote_host = "www.google.com"; 
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  Serial.println("Wifi Terhubung...");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(relay, HIGH);
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  Serial.println("Disconnected...");
  WiFi.disconnect();
  WiFi.begin(ssid, pass);
  digitalWrite(ledPin, HIGH);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(relay, LOW);
}


void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(relay, OUTPUT);
    wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
    wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
    setupWifi();
    Serial.print("RSSI: ");
    Serial.println(WiFi.RSSI());
    Blynk.begin(auth, ssid, pass, "iot.serangkota.go.id", 8080);
    FastLED.addLeds<LED_TYPE, PIN1, COLOR_ORDER>(leds1, NUM_LEDS1).setCorrection( TypicalLEDStrip );
//    setupBotTele();
    setupYoutube();
    setupSensor();
}

void loop() 
{
  cekInternet();
  Blynk.run();
  timer.run();
  Duco_view();
  youtubesubs();
  InfoDevice();
}
