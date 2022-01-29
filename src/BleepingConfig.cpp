#include "BleepingConfig.h"

BleepingConfig::BleepingConfig() {
  this->conf = new Preferences();
}

boolean BleepingConfig::init() {
  boolean load = conf->begin(_BLib, false);
  String loadS = load ? "" : "not ";
  ESP_LOGD(_BLib, "Config %sloaded.", loadS);

  if(!load) {
    return false;
  }

  putString(BleepingProperty::HardwareBoots, String(getBootCycles() + 1).c_str());
  return getBootCycles();
}

/**
 * Used to initialize the NVS flash on the device.
 * This is the equivelent of a 'factory reset'
 */
void BleepingConfig::formatAndReboot() {

  ESP_LOGI(_BLib, "Formatting NVS.");
  nvs_flash_erase();
  nvs_flash_init();

  ESP_LOGI(_BLib, "Rebooting.");
  ESP.restart();
}

int BleepingConfig::getBootCycles() {
  return getString(BleepingProperty::HardwareBoots).toInt();
}

boolean BleepingConfig::isConfigured() {
  return conf->getBool(key(BleepingProperty::HardwareConfigured).c_str());
}

String BleepingConfig::getString(const char* name) {
  return conf->getString(key(name).c_str());
}

String BleepingConfig::getString(BleepingProperty name) {
  return conf->getString(key(name).c_str());
}

void BleepingConfig::putString(const char* name, const char* val) {
  conf->putString(key(name).c_str(), val);
}

void BleepingConfig::putString(BleepingProperty name, const char* val) {
  conf->putString(key(name).c_str(), val);
}

String BleepingConfig::key(const char* uuid) {
  return String(uuid).substring(21, 30);
}

String BleepingConfig::key(BleepingProperty name) {
  return key(BleepingUUID(name).toString().c_str());
}
