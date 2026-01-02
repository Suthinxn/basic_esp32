#pragma once
#include <BLECharacteristic.h>

// ประกาศตัวแปร (ยังไม่สร้างจริง)
extern bool deviceConnected;
extern BLECharacteristic *pCharacteristic;

// function
void runSetup();
void runLoop();
