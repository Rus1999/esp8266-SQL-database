#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "DHT.h"

const char* ssid = "rus";
const char* password = "77777777";

#define DHTTYPE DHT11 
const int DHT1Pin = D1; // D1 5
const int DHT2Pin = D2; // D5 14
const int DHT3Pin = D3;
DHT dht1(DHT1Pin, DHTTYPE);
DHT dht2(DHT2Pin, DHTTYPE);
DHT dht3(DHT3Pin, DHTTYPE);

WiFiClient espClient;
ESP8266WiFiMulti wifiMulti;

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  Serial.begin(115200);
  setup_wifi();
  dht1.begin();
  dht2.begin();
  dht3.begin();
}

void loop() {
  Serial.println("--------------------------");
  // *****************************
  delay(1000);
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  delay(1000);
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  delay(1000);
  float h3 = dht3.readHumidity();
  float t3 = dht3.readTemperature();
  delay(1000);
  
  Serial.print("Sensor 1: ");
  Serial.print("Humidity: ");
  Serial.print(h1);
  Serial.print(" %\t Temperature: ");
  Serial.print(t1);
  Serial.println(" *C ");

  Serial.print("Sensor 2: ");
  Serial.print("Humidity: ");
  Serial.print(h2);
  Serial.print(" %\t Temperature: ");
  Serial.print(t2);
  Serial.println(" *C ");

  Serial.print("Sensor 3: ");
  Serial.print("Humidity: ");
  Serial.print(h3);
  Serial.print(" %\t Temperature: ");
  Serial.print(t3);
  Serial.println(" *C ");

  HTTPClient http;

  http.begin(espClient, "http://192.168.43.183/esp8266/multi/add.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST("t1=" + String(t1) + "&h1=" + String(h1) + "&t2=" + String(t2) + "&h2=" + String(h2) + "&t3=" + String(t3) + "&h3=" + String(h3));

  if (httpCode > 0) 
  {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) 
    {
      String payload = http.getString();
      Serial.println(payload);
    }
  } 
  else 
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  delay(5000);
}
