#ifdef PMS7003_WITH_BLUETOOTH

#include "pms7003_with_bluetooth.h"
#include <Arduino.h>
#include <HardwareSerial.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// ================= PMS7003 =================
HardwareSerial pmsSerial(1);

static uint16_t pm1  = 0;
static uint16_t pm25 = 0;
static uint16_t pm10 = 0;

static unsigned long lastSendTime = 0;
const unsigned long SEND_INTERVAL = 30000; // 30 วินาที


// ================= BLE (define จริงที่นี่ที่เดียว) =================
BLECharacteristic *pCharacteristic = nullptr;
bool deviceConnected = false;

// UUID
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-ba0987654321"

// ================= BLE callback =================
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) override {
    deviceConnected = true;
    Serial.println("[BLE] Connected");
  }

  void onDisconnect(BLEServer* pServer) override {
    deviceConnected = false;
    Serial.println("[BLE] Disconnected");
    BLEDevice::startAdvertising();
  }
};

// ================= Setup =================
void runSetup() {
  Serial.begin(115200);

  // PMS7003 UART
  pmsSerial.begin(9600, SERIAL_8N1, 18, 19);
  Serial.println("[PMS7003] UART started");

  // BLE init
  BLEDevice::init("ESP32_PM");

  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_NOTIFY
  );

  // Descriptor จำเป็นสำหรับ nRF Connect
  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->start();

  Serial.println("[BLE] Advertising started");
}

// ================= PMS7003 read =================
static bool readPMS() {
  if (pmsSerial.available() < 32) return false;

  uint8_t buffer[32];
  pmsSerial.readBytes(buffer, 32);

  if (buffer[0] != 0x42 || buffer[1] != 0x4D) {
    Serial.println("[PMS7003] Invalid header");
    return false;
  }

  pm1  = (buffer[4] << 8) | buffer[5];
  pm25 = (buffer[6] << 8) | buffer[7];
  pm10 = (buffer[8] << 8) | buffer[9];

  Serial.printf("[PMS7003] PM1:%d PM2.5:%d PM10:%d\n",
                pm1, pm25, pm10);

  return true;
}

// ================= Loop =================
void runLoop() {
  unsigned long now = millis();

  // ตรวจว่าครบ 30 วินาทีหรือยัง
  if (now - lastSendTime >= SEND_INTERVAL) {
    lastSendTime = now;

    if (readPMS()) {
      if (deviceConnected && pCharacteristic != nullptr) {

        char payload[64];
        snprintf(payload, sizeof(payload),
          "{\"pm1\":%d,\"pm25\":%d,\"pm10\":%d}",
          pm1, pm25, pm10
        );

        pCharacteristic->setValue(
          (uint8_t*)payload,
          strlen(payload)
        );
        pCharacteristic->notify();

        Serial.println("[BLE] Data sent (30s)");
      }
    }
  }
}


#endif
