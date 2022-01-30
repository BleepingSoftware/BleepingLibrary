/**
   BleepingExample

   An example ESP32 sketch using the Bleep App and Library

   This example will start a BLE server allowing a user to configure WiFi credentials.
   Once the device has been configured and rebooted, it will connect to WiFi and be ready to serve your application.

   Read more in the Getting Started guide.
   https://github.com/MClarkDev/BleepingLibrary/blob/master/GettingStarted.md
*/
#include "BleepingLibrary.h"
#include "BleepingConfig.h"

#include <WiFi.h>

BleepingLibrary bLib;

void setup() {

  // Initialize
  int boots = bLib.init();
  ESP_LOGI(_BLib, "Boots: %d", boots);

  // Is already configured?
  if (!bLib.isConfigured()) {

    // Start setup mode, 2 minute timeout
    // Sleep if still not configured
    if (!bLib.beginSetup(120 * 1000)) {
      esp_deep_sleep_start();
    }
  }

  /**
     Implement your code below!
  */

  ESP_LOGI(_BLib, "Now running my Bleeping App!");

  // Load WiFi connection properties from bleeping config
  String netName = bLib.getString(BleepingProperty::NetworkName);
  String netPass = bLib.getString(BleepingProperty::NetworkPassword);

  ESP_LOGI(_BLib, "Connecting to: %s", netName.c_str());

  WiFi.mode(WIFI_STA);
  WiFi.begin(netName.c_str(), netPass.c_str());
}

boolean connected = false;

void loop() {
  if (WiFi.status() == WL_CONNECTED && !connected) {
    ESP_LOGI(_BLib, "Ready.");
    connected = true;
  }

  delay(10);
}
