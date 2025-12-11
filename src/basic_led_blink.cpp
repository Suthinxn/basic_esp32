#ifdef BASIC_LED_BLINK
#include <Arduino.h>

void runSetup() {
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    Serial.println("FLAG: BASIC_SERIAL_MONITOR ");
}

void runLoop() {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
}
#endif
