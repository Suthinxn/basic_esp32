#ifdef BASIC_SENSOR_PMS7003
#include <Arduino.h>
#include <HardwareSerial.h>







HardwareSerial pmsSerial(1);  // ใช้ Serial1

// unsigned int pm1 = 0;
// unsigned int pm2_5 = 0;
// unsigned int pm10 = 0;

uint16_t pm1 = 0;
uint16_t pm2_5 = 0;
uint16_t pm10 = 0;



void runSetup() {
    Serial.begin(115200);

    // ตั้งค่า UART1: RX=21, TX=22
    pmsSerial.begin(9600, SERIAL_8N1, 18, 19);

    Serial.println("ESP32 ready.");
}

bool read_pm_sensor() {

    // รอจนกว่าจะมี header
    while (pmsSerial.available() >= 2) {
        if (pmsSerial.read() == 0x42) {
            if (pmsSerial.peek() == 0x4D) {
                pmsSerial.read(); // consume 0x4D

                uint8_t buffer[30];
                if (pmsSerial.readBytes(buffer, 30) != 30) {
                    return false;
                }

                // ตรวจ checksum
                uint16_t checksum = 0x42 + 0x4D;
                for (int i = 0; i < 28; i++) {
                    checksum += buffer[i];
                }

                uint16_t recv_checksum =
                    (buffer[28] << 8) | buffer[29];

                if (checksum != recv_checksum) {
                    Serial.println("Checksum error");
                    return false;
                }

                // ตาม datasheet (Atmospheric Environment)
                pm1   = (buffer[4] << 8) | buffer[5];
                pm2_5 = (buffer[6] << 8) | buffer[7];
                pm10  = (buffer[8] << 8) | buffer[9];

                Serial.printf("PM1: %u  PM2.5: %u  PM10: %u\n",
                              pm1, pm2_5, pm10);

                return true;
            }
        }
    }
    return false;
}

void runLoop() {
    if (!read_pm_sensor()) {
        Serial.println("No valid PMS7003 data");
    }
    delay(1000);
}

#endif
