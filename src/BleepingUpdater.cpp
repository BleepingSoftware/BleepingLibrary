/**
   BleepingLibrary!
   MClarkDev.com, 2022
   BleepingUpdater.cpp
*/

#include <BleepingUpdater.h>

BleepingUpdater::BleepingUpdater(BleepingConfig* conf) {
  this->conf = conf;
}

boolean BleepingUpdater::doUpdate() {
  return doUpdate(conf->getString(BleepingProperty::UpdateTarget).c_str());
}

boolean BleepingUpdater::doUpdate(const char* target) {
  ESP_LOGD(_BLib, "Updating: %s", target);

  // Load WiFi connection properties from bleeping config
  String netName = conf->getString(BleepingUUID(BleepingProperty::NetworkName));
  String netPass = conf->getString(BleepingUUID(BleepingProperty::NetworkPassword));
  ESP_LOGI(_BLib, "Connecting to: %s", netName.c_str());

  WiFi.mode(WIFI_STA);
  WiFi.begin(netName.c_str(), netPass.c_str());

  // Connect, 30s timeout
  int timeout = millis() + (30 * 1000);
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() > timeout) {
      return false;
    }
    delay(25);
  }

  t_httpUpdate_return ret = httpUpdate.update(client, target);

  if (ret != HTTP_UPDATE_OK) {
    ESP_LOGE(TAG, "Update failed. Error (%d): %s\n", //
             httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
    return false;
  }

  ESP_LOGI(TAG, "Update complete.");
  ESP.restart();
  return true;
}

void BleepingUpdater::onWrite(BLECharacteristic *characteristic) {
  std::string key = characteristic->getUUID().toString();
  std::string val = characteristic->getValue();
}

void BleepingUpdater::onRead(BLECharacteristic* characteristic) {
  std::string key = characteristic->getUUID().toString();
  std::string val = characteristic->getValue();
}
