#ifdef BASIC_SENSOR_PMS7003
#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial mySerial(1);  // ใช้ Serial1

unsigned int pm1 = 0;
unsigned int pm2_5 = 0;
unsigned int pm10 = 0;

void runSetup() {
    Serial.begin(115200);

    // ตั้งค่า UART1: RX=21, TX=22
    mySerial.begin(9600, SERIAL_8N1, 18, 19);

    Serial.println("ESP32 ready.");
}

void read_pm_sensor() {

    // ต้องมีอย่างน้อย 32 bytes ถึงจะเป็นแพ็กเก็ตของ PMS7003
    if (mySerial.available() < 32) {
        Serial.println(mySerial.available());
        Serial.println("return");
        return;
    }

    uint8_t buffer[32];

    // อ่านข้อมูลทั้งหมด 32 bytes
    mySerial.readBytes(buffer, 32);

    // ตรวจ header 0x42 0x4D
    if (buffer[0] != 0x42 || buffer[1] != 0x4D) {
        Serial.println("Header not found");
        return;
    }

    // อ่านค่าตาม datasheet
    pm1   = buffer[4] * 256 + buffer[5];
    pm2_5 = buffer[6] * 256 + buffer[7];
    pm10  = buffer[8] * 256 + buffer[9];

    Serial.print("PM1: ");
    Serial.print(pm1);
    Serial.print("  PM2.5: ");
    Serial.print(pm2_5);
    Serial.print("  PM10: ");
    Serial.println(pm10);
}

void runLoop() {
    Serial.println("Test");
    read_pm_sensor();
    delay(1000);
}

#endif
