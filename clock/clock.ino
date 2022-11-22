//includes
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

//constants
#define ssid "ATL LAB"
#define pass "atl@12345"

//globals
WiFiClient client;
String doom;
const char* host = "https://climateclockapi.opgamer3000pro.repl.co";
const char* api_rtc = "https://climateclockapi.opgamer3000pro.repl.co/rtc";
const char* api_timeLeft = "https://climateclockapi.opgamer3000pro.repl.co/timeLeft";

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

  http.begin(client, api_rtc);

  int HTTPcode = http.GET();
  Serial.println(HTTPcode);
  if(HTTPcode == 200){
    doom = http.getString();
    Serial.println(doom);
  }
}

void loop(){
}

String getNet(const char* host, const char* url){
  WiFiClientSecure client;
  HTTPClient http;
}