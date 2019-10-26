#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "xxxx";
const char* pass = "xxxx";
bool WiFiConnected = false;


void setup() {
    Serial.begin(115200);
    WiFi.disconnect(true);  // delete old config

    delay(1000);
/*
 * hàm này là con trỏ cho hàm
 */
    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
      Serial.print("WiFi connected. IP: ");
      Serial.println(IPAddress(info.got_ip.ip_info.ip.addr));
      WiFiConnected = true;
    }, WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);
    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info){
        Serial.print("WiFi lost connection. Reason: ");
        Serial.println(info.disconnected.reason);
        WiFi.disconnect();
        WiFiConnected = false;
    }, WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED);

    WiFi.begin(ssid, pass);

    Serial.println();
    Serial.println("Connecting to WiFi... ");
}

void loop() {

}
