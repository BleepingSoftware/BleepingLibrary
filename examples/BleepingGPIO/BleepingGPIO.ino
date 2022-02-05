/**
   BleepingGPIO

   An example ESP32 sketch using the Bleep App and Library

   Read more in the Getting Started guide.
   https://github.com/MClarkDev/BleepingLibrary/blob/master/GettingStarted.md
*/

#include "BleepingLibrary.h"
#include <BLEDevice.h>

#define GPIO_PIN 2

BleepingLibrary bLib;

BleepingUUID myGPIOService = BleepingUUID("00000000-0000-0000-002f-000000000000");
BleepingUUID myGPIOPinState = BleepingUUID("00000000-0000-0000-002f-ff0003000000");

class MyBleepingCallback: public BLECharacteristicCallbacks {
  void onRead(BLECharacteristic* characteristic) {
    std::string key = characteristic->getUUID().toString();

    if (key == myGPIOPinState.toString().c_str()) {
      characteristic->setValue(String(digitalRead(GPIO_PIN)).c_str());
      return;
    }
  }

  void onWrite(BLECharacteristic *characteristic) {
    std::string key = characteristic->getUUID().toString();
    std::string val = characteristic->getValue();

    if (key == myGPIOPinState.toString().c_str()) {
      digitalWrite(GPIO_PIN, val != "0");
      return;
    }
  }
};

void setup() {

  // Initialize
  int boots = bLib.init();
  ESP_LOGI(_BLib, "Boots: %d", boots);
  pinMode(GPIO_PIN, OUTPUT);

  // Setup BLE server
  BleepingServer* server = bLib.getServer();
  server->startServer();

  // Add Custom Service
  MyBleepingCallback* myCallback = new MyBleepingCallback();
  BLEService* myService = server->createService(myGPIOService, 4);
  server->createCharacteristic(myService, myGPIOPinState, myCallback);
  myService->start();

  /**
    Implement your code below!
  */

  ESP_LOGI(_BLib, "Now running my Bleeping App!");
  ESP_LOGI(_BLib, "Setup mode is still running!");
}

void loop() {
}
