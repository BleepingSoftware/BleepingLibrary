/**
   BleepingLibrary!
   MClarkDev.com, 2022
   BleepingUpdater.cpp
*/

#include <BleepingUpdater.h>

BleepingUpdater::BleepingUpdater(BleepingConfig* conf) {
  this->conf = conf;
}

void BleepingUpdater::doUpdate() {
  doUpdate(conf->getString(BleepingProperty::UpdateTarget).c_str());
}

void BleepingUpdater::doUpdate(const char* target) {
  ESP_LOGD(_BLib, "Updating: %s", target);

  // Load WiFi connection properties from bleeping config
  String netName = conf->getString(BleepingUUID(BleepingProperty::NetworkName));
  String netPass = conf->getString(BleepingUUID(BleepingProperty::NetworkPassword));

  ESP_LOGI(_BLib, "Connecting to: %s", netName.c_str());

  WiFi.mode(WIFI_STA);
  WiFi.begin(netName.c_str(), netPass.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(25);
  }

  t_httpUpdate_return ret = httpUpdate.update(client, target);

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      ESP_LOGE(TAG, "Update failed. Error (%d): %s\n", //
               httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
      break;

    case HTTP_UPDATE_OK:
      ESP_LOGI(TAG, "Update complete.");
      ESP.restart();
      break;

    default:
      break;
  }
}

void BleepingUpdater::onWrite(BLECharacteristic *characteristic) {
  std::string key = characteristic->getUUID().toString();
  std::string val = characteristic->getValue();
}

void BleepingUpdater::onRead(BLECharacteristic* characteristic) {
  std::string key = characteristic->getUUID().toString();
  std::string val = characteristic->getValue();
}