#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <ESPAsync_WiFiManager.h>  



AsyncWebServer server(80);

DNSServer dnsServer;


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); while (!Serial); delay(200);
  Serial.print("\nStarting Async_AutoConnect_ESP32_minimal on " + String(ARDUINO_BOARD)); Serial.println(ESP_ASYNC_WIFIMANAGER_VERSION);

  ESPAsync_WiFiManager ESPAsync_wifiManager(&server, &dnsServer, "Async_AutoConnect");

  //ESPAsync_wifiManager.resetSettings();   //reset saved settings
  ESPAsync_wifiManager.autoConnect("Dan-AP");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print(F("Connected. Local IP: ")); Serial.println(WiFi.localIP()); }
  else {
    Serial.println(ESPAsync_wifiManager.getStatus(WiFi.status())); 
    }
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  request->send(200, "text/plain", "Hi! I am ESP32.");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {  }