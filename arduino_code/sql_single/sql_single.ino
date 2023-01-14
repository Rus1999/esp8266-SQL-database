#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define DHTPIN D3
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

WiFiClient wifiClient;
ESP8266WiFiMulti wifiMulti;
// DHT dht;
void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("rus", "77777777");
  // dht.setup(D5);
}

void loop() 
{
  if (wifiMulti.run() != WL_CONNECTED) 
  {
    Serial.println("WiFi not connected!");
    delay(1000);
  }
  else
  {
    float temp = dht.readTemperature();
    float humid = dht.readHumidity();
    
    Serial.print("Temperature : ");
    Serial.println(temp);
    Serial.print("Humidity: ");
    Serial.println(humid);

    HTTPClient http;
    // String url = "http://192.168.43.183/esp8266/single/add.php?temp=" + String(temp) + "&humid=" + String(humid);
    // Serial.println(url);
    // http.begin(wifiClient,url); //HTTP
    // int httpCode = http.GET();

    http.begin(wifiClient, "http://192.168.43.183/esp8266/single/add_post.php"); //HTTP
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST("temp=" + String(temp) + "&humid=" + String(humid));

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
  delay(5000);
}

