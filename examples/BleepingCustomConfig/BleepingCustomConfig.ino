/**
   BleepingCustomConfig

   An example ESP32 sketch using the Bleep App and Library

   This example will start a BLE server allowing a user to configure WiFi credentials.
   It uses methods exposed by the BleepingLibrary to implement custom configuration properties.

   Read more in the Getting Started guide.
   https://github.com/MClarkDev/BleepingLibrary/blob/master/GettingStarted.md
*/

#include "BleepingLibrary.h"

BleepingLibrary bLib;

BleepingUUID myUUID_R = BleepingUUID("00000000-0000-0000-002f-ff0001000000");
BleepingUUID myUUID_W = BleepingUUID("00000000-0000-0000-002f-ff0002000000");
BleepingUUID myUUID_RW = BleepingUUID("00000000-0000-0000-002f-ff0003000000");

BleepingUUID uuids[] = { myUUID_R, myUUID_W, myUUID_RW };

void setup() {

  // Initialize
  int boots = bLib.init();
  ESP_LOGI(_BLib, "Boots: %d", boots);

  // Setup BLE server
  BleepingServer* server = bLib.getServer();
  server->startServer();

  // Custom Config Parameters
  server->startCustomPropertyService(uuids, 3);

  /**
    Implement your code below!
  */
  ESP_LOGI(_BLib, "Now running my Bleeping App!");
  ESP_LOGI(_BLib, "Setup mode is still running!");

  int timeout = millis() + (5 * 60 * 1000);
  while (millis() < timeout) {
    String val = bLib.getConfig()->getString(myUUID_W);
    ESP_LOGD(_BLib, "Got: %s", val.c_str());
    delay(1000);
  }

  ESP.restart();
}

void loop() {
}