#ifdef BASIC_UART
#include <Arduino.h>

void runSetup() {
    Serial.begin(115200);
    Serial.setTimeout(100);

}

void runLoop() {
  if (Serial.available() > 0) {
    String msg = Serial.readString();
    Serial.print("Echo: ");
    Serial.println(msg);
  }
}
#endif
