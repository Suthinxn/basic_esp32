#ifdef BASIC_READ_ESP32_INFO
#include <Arduino.h>

void runSetup() {
    Serial.begin(115200);

    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    Serial.println("ESP32 Chip Info:");
    Serial.printf("Cores: %d\n", chip_info.cores);

    switch (chip_info.model) {
        case CHIP_ESP32:
        Serial.println("Model: ESP32");
        break;
        case CHIP_ESP32S2:
        Serial.println("Model: ESP32-S2");
        break;
        case CHIP_ESP32S3:
        Serial.println("Model: ESP32-S3");
        break;
        case CHIP_ESP32C3:
        Serial.println("Model: ESP32-C3");
        break;
        default:
        Serial.println("Model: Unknown");
        break;
    }

    Serial.print("Features: ");
    if (chip_info.features & CHIP_FEATURE_WIFI_BGN) Serial.print("WiFi ");
    if (chip_info.features & CHIP_FEATURE_BT)       Serial.print("BT ");
    if (chip_info.features & CHIP_FEATURE_BLE)      Serial.print("BLE ");
    Serial.println();
    Serial.printf("PSRAM: %s\n", psramFound() ? "Yes" : "No"); // Yes = WROVER , NO = WROOM-32
}

void runLoop() {

}

#endif 