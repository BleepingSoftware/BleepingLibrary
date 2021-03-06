/**
   BleepingOTAUpdate

   An example ESP32 sketch using the Bleep App and Library

   Read more in the Getting Started guide.
   https://github.com/MClarkDev/BleepingLibrary/blob/master/GettingStarted.md
*/

#define OTA_APPNAME "BleepingOTAUpdate"
#define OTA_VERSION 1

#include "BleepingLibrary.h"

BleepingLibrary bLib;

void setup() {

  // Initialize
  int boots = bLib.init();
  ESP_LOGI(_BLib, "Boots: %d", boots);

  // Check for updates
  bLib.enableUpdater(OTA_APPNAME, OTA_VERSION);
  if(bLib.getUpdater()->checkUpdateAvailable()) {
    bLib.getUpdater()->doUpdate();
  }

  /**
    Implement your code below!
  */
  ESP_LOGI(_BLib, "Now running my Bleeping App!");
  ESP_LOGI(_BLib, "Setup mode is still running!");
}

void loop() {
  delay(1000);
  ESP_LOGI(_BLib, "Now running my Bleeping App!");
}