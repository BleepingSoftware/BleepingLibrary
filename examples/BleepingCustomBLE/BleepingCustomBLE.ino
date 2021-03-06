/**
   BleepingCustomBLE

   An example ESP32 sketch using the Bleep App and Library

   This example will start a BLE server allowing a user to configure WiFi credentials.
   It uses methods exposed by the BleepingLibrary to implement custom BLE callbacks.

   Read more in the Getting Started guide.
   https://github.com/MClarkDev/BleepingLibrary/blob/master/GettingStarted.md
*/

#include "BleepingLibrary.h"
#include <BLEDevice.h>

BleepingLibrary bLib;

class MyBleepingCallback: public BLECharacteristicCallbacks {
    void onRead(BLECharacteristic* characteristic) {
      std::string key = characteristic->getUUID().toString();
      std::string val = characteristic->getValue();
      ESP_LOGD(_BLib, "Read: %s :: %s", key.c_str(), val.c_str());
    }

    void onWrite(BLECharacteristic *characteristic) {
      std::string key = characteristic->getUUID().toString();
      std::string val = characteristic->getValue();
      ESP_LOGD(_BLib, "Write: %s :: %s", key.c_str(), val.c_str());
    }
};

void setup() {

  // Initialize
  int boots = bLib.init();
  ESP_LOGI(_BLib, "Boots: %d", boots);

  // Setup BLE server
  BleepingServer* server = bLib.getServer();
  server->startServer();

  // Add Custom Service
  MyBleepingCallback* myCallback = new MyBleepingCallback();
  BLEService* myService = server->createService(BleepingUUID("00000000-0000-beef-003f-000000000000"), 7);
  server->createCharacteristic(myService, BleepingUUID("00000000-0000-beef-003f-000001000000"), myCallback);
  server->createCharacteristic(myService, BleepingUUID("00000000-0000-beef-003f-000002000000"), myCallback);
  server->createCharacteristic(myService, BleepingUUID("00000000-0000-beef-003f-000003000000"), myCallback);
  myService->start();

  /**
    Implement your code below!
  */

  ESP_LOGI(_BLib, "Now running my Bleeping App!");
  ESP_LOGI(_BLib, "Setup mode is still running!");

  int timeout = millis() + (2 * 60 * 1000);
  while (millis() < timeout) {
    delay(10);
  }
  ESP.restart();
}

void loop() {
}
