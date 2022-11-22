//includes
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

//constants
#define ssid "JioFiber-6G9Mq"
#define pass "12345678"
/*const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 
      2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 
      JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 390;*/

//globals
WiFiClient client;
String doom;
const char* host PROGMEM = "https://api.climateclock.world";
const char* api PROGMEM = "https://api.climateclock.world/v2/clock.json";
const size_t cap = 40000;

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }

  Serial.println();
  Serial.println(WiFi.localIP());

  WiFiClientSecure client;
  HTTPClient http;
  
  client.setInsecure(); //the magic line
  client.connect(host, 443);

  http.begin(client, api);

  int HTTPcode = http.GET();
  if(HTTPcode == 200){
    doom = http.getString();
    Serial.print(doom);
    DynamicJsonDocument doom_json(cap);
    DeserializationError error = deserializeJson(doom_json, doom);
    Serial.println(doom_json.capacity());

    if(error){
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      while(true);
    }
    
    JsonObject data = doom_json["data"];
    JsonObject data_modules = data["modules"];
    JsonObject data_modules_carbon_deadline_1 = data_modules["carbon_deadline_1"];
    const char* timestamp = data_modules_carbon_deadline_1["timestamp"];
    
    Serial.print("FINAL DATA: ");
    Serial.println(timestamp);
  } else {
    Serial.printf("error while GET(): %d\n", HTTPcode);
    while(true);
  }
}

void loop(){
}