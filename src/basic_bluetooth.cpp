#ifdef BASIC_BLUETOOTH
#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define LED 2


void runSetup() {
    SerialBT.begin("ESP32");
    pinMode(LED, OUTPUT);
}

void runLoop() {
    char message;

    if (SerialBT.available())
    {
        message=SerialBT.read();
        if (message == '1')
        {
            digitalWrite(LED, HIGH);
        }
        else if (message == '0')
        {
            digitalWrite(LED, LOW);
        }
    }
    delay(20);
}
#endif