#ifdef BASIC_WIFI_STA_MODE
#include <Arduino.h>
#include<WiFi.h>

#define WIFI_STA_NAME ""
#define WIFI_STA_PASS ""


void runSetup() {
    Serial.begin(115200);
    Serial.println("FLAG: BASIC_WIFI_STA_MODE ");
    pinMode(2, OUTPUT);

    Serial.println();
    Serial.println();
    Serial.print("Connectin to ");
    Serial.println(WIFI_STA_NAME);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        digitalWrite(2, !digitalRead(2));
    }

    digitalWrite(2, HIGH);
    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

}

void runLoop() {
}
#endif
