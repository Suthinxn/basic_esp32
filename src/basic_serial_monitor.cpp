#ifdef BASIC_SERIAL_MONITOR
#include <Arduino.h>

void runSetup() {
    Serial.begin(115200);
    Serial.println("FLAG: BASIC_SERIAL_MONITOR ");
}

void runLoop() {
}
#endif
