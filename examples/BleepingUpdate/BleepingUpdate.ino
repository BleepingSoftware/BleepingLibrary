/**
   BleepingExample

   An example ESP32 sketch using the Bleep App and Library

   BLE ESP Provisioning allows users to provision their device and set
   additional configuration parmaters using an easy to implement protocol.
*/
#include "BleepingLibrary.h"

#define TARGET "http://files.mclarkdev.com/uploads/Default.ino.esp32.bin"

BleepingLibrary bLib;

void setup() {

  // Initialize
  int boots = bLib.init();
  ESP_LOGI(_BLib, "Boots: %d", boots);

  // Is already configured?
  if(!bLib.isConfigured()) {

    // Start setup mode, 2 minute timeout
    // Sleep if still not configured
    if(!bLib.beginSetup(120 * 1000)) {
      esp_deep_sleep_start();
    }
  }

  // Run updater
  bLib.getUpdater()->doUpdate(TARGET);
}

void loop() {
  delay(1000);
  ESP_LOGI(_BLib, "Now running my Bleeping App!");
}
