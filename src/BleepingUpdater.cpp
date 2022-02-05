/**
   BleepingLibrary!
   MClarkDev.com, 2022
   BleepingUpdater.cpp
*/

#include <BleepingUpdater.h>

BleepingUpdater::BleepingUpdater(BleepingConfig* conf, const char* app, int ver) {
  this->conf = conf;
  this->app = app;
  this->ver = ver;
}

boolean BleepingUpdater::connect() {
  if(WiFi.status() == WL_CONNECTED) {
    return true;
  }

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

  return true;
}

boolean BleepingUpdater::checkUpdateAvailable() {
  if (!connect()) {
    ESP_LOGW(_BLib, "Failed to connect.");
    return false;
  }

  ESP_LOGD(_BLib, "Checking for updates...");

  String url = "http://devices.bleepingsoftware.com/ping/";
  url += "?app=";
  url += app;
  url += "&mac=";
  url += String(WiFi.macAddress().c_str());
  url += "&ver=";
  url += String(ver);

  String response = fetch(url);
  ESP_LOGD(_BLib, "Got: %s", response.c_str());
  return true;
}

boolean BleepingUpdater::doUpdate() {
 
  if (!connect()) {
    return false;
  }

  String url = "http://devices.bleepingsoftware.com/update/";
  url += "?app=";
  url += app;
  url += "&mac=";
  url += String(WiFi.macAddress().c_str());
  url += "&ver=";
  url += String(ver);

  ESP_LOGD(_BLib, "Updating: %s", url.c_str());

  t_httpUpdate_return ret = httpUpdate.update(client, url);

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

  if (key == BleepingUUID(BleepingSystem::FirmwareUpdate).toString().c_str()) {
    doUpdate();
    return;
  }
}

void BleepingUpdater::onRead(BLECharacteristic* characteristic) {
  std::string key = characteristic->getUUID().toString();
  std::string val = characteristic->getValue();

  if (key == BleepingUUID(BleepingSystem::FirmwareSDK).toString().c_str()) {
    characteristic->setValue(ESP.getSdkVersion());
    return;
  }

  if (key == BleepingUUID(BleepingSystem::FirmwareCurrent).toString().c_str()) {
    characteristic->setValue(String(ver).c_str());
    return;
  }

  if (key == BleepingUUID(BleepingSystem::FirmwareLatest).toString().c_str()) {
    boolean updateAvail = checkUpdateAvailable();
	characteristic->setValue(String(updateAvail).c_str());
	return;
  }
}

String BleepingUpdater::fetch(String url) {
  ESP_LOGD(_BLib, "Fetching: %s", url.c_str());

  HTTPClient http;
  http.begin(url.c_str());
  int code = http.GET();
  if (code <= 0) {
    ESP_LOGE(_BLib, "API Error: %d", code);
    return "";
  }

  String body = http.getString();
  http.end();
  return body;
}
