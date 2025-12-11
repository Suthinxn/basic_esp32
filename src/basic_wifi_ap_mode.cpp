#ifdef BASIC_WIFI_AP_MODE
#include <Arduino.h>
#include<WiFi.h>

#define WIFI_AP_NAME "ESP32 AP mode"
// #define WIFI_AP_PASS NULL
#define WIFI_AP_PASS "password"


void runSetup() {
    Serial.begin(115200);
    Serial.println("FLAG: BASIC_WIFI_AP_MODE ");

    WiFi.mode(WIFI_AP);
    WiFi.softAP(WIFI_AP_NAME, WIFI_AP_PASS);

    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
}

void runLoop() {
}
#endif
