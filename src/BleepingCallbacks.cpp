/**
   BleepingLibrary!
   MClarkDev.com, 2022
   BleepingCallbacks.cpp
*/

#include "BleepingCallbacks.h"

BleepingSystemCallback::BleepingSystemCallback(BleepingConfig* conf) {
  this->conf = conf;
}

void BleepingSystemCallback::onWrite(BLECharacteristic *pCharacteristic) {
  std::string key = pCharacteristic->getUUID().toString();
  std::string val = pCharacteristic->getValue();

  if (key == BleepingUUID(BleepingSystem::HardwareRestart).toString().c_str()) {
    ESP.restart();
    return;
  }

  if (key == BleepingUUID(BleepingSystem::HardwareReset).toString().c_str()) {
    conf->formatAndReboot();
    return;
  }
}

void BleepingSystemCallback::onRead(BLECharacteristic* pCharacteristic) {
  std::string key = pCharacteristic->getUUID().toString();
  std::string val = pCharacteristic->getValue();

  if (key == BleepingUUID(BleepingSystem::HardwareUptime).toString().c_str()) {
    pCharacteristic->setValue(String(millis()).c_str());
    return;
  }

  if (key == BleepingUUID(BleepingSystem::HardwareMAC).toString().c_str()) {
    pCharacteristic->setValue(WiFi.macAddress().c_str());
    return;
  }
}

BleepingPropertyCallback::BleepingPropertyCallback(BleepingConfig* conf) {
  this->conf = conf;

  lastT = 0;
  lastK = "";
  continued = false;
}

void BleepingPropertyCallback::onWrite(BLECharacteristic *characteristic) {
  std::string key = characteristic->getUUID().toString();
  std::string val = characteristic->getValue();

  continued = (key == lastK) && (millis() < lastT + 750);
  lastT = millis();
  lastK = key;

  if (continued) {
    val.insert(0, conf->getString(key.c_str()).c_str());
  }

  conf->putString(key.c_str(), val.c_str());
  ESP_LOGD(_BLib, "Set [ %s :: %s ]", key.c_str(), val.c_str());
}

void BleepingPropertyCallback::onRead(BLECharacteristic* characteristic) {
  std::string key = characteristic->getUUID().toString();
  std::string val = characteristic->getValue();

  String prop = conf->getString(key.c_str());
  characteristic->setValue(prop.c_str());
  ESP_LOGD(_BLib, "Got [ %s :: %s ]", key.c_str(), prop.c_str());
}
