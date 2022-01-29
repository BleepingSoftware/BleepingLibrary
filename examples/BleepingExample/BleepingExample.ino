/**
   BleepingExample

   An example ESP32 sketch using the Bleep App and Library

   BLE ESP Provisioning allows users to provision their device and set
   additional configuration parmaters using an easy to implement protocol.
*/
#include "BleepingLibrary.h"
#include "BleepingConfig.h"

#include <WiFi.h>

BleepingLibrary bLib;

void setup() {

  // Initialize
  int boots = bLib.init();
  ESP_LOGI(_BLib, "Boots: %d", boots);

  // Get configuration
  BleepingConfig* conf = bLib.getConfig();

  // Is already configured?
  if(!conf->isConfigured()) {

    // Start setup mode, 2 minute timeout
    // Sleep if still not configured
    if(!bLib.beginSetup(120 * 1000)) {
      esp_deep_sleep_start();
    }
  }

  /**
   * Implement your code below!
   */

  ESP_LOGI(_BLib, "Now running my Bleeping App!");

  // Load WiFi connection properties from bleeping config
  const char* netName = conf->getString(BleepingProperty::NetworkName).c_str();
  const char* netPass = conf->getString(BleepingProperty::NetworkPassword).c_str();

  ESP_LOGI(_BLib, "Connecting [ %s :: %s ]", netName, netPass);

  WiFi.mode(WIFI_STA);
  WiFi.begin(netName, netPass);
}

boolean connected = false;

void loop() {
  if (WiFi.status() == WL_CONNECTED && !connected) {
    ESP_LOGI(_BLib, "Ready.");
    connected = true;
  }

  delay(10);
}
