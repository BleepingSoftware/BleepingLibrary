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

String BleepingConfig::getString(BleepingUUID uuid) {

  String s2 = uuid.toString().substring(21, 30);
  const char* key = s2.c_str();

  String val = conf->getString(key);
  ESP_LOGD(_BLib, "Got [ %s :: %s ]", key, val.c_str());
  return val;
}

void BleepingConfig::putString(BleepingUUID uuid, const char* val) {

  String s2 = uuid.toString().substring(21, 30);
  const char* key = s2.c_str();

  conf->putString(key, String(val).c_str());
  ESP_LOGD(_BLib, "Put [ %s :: %s ]", key, val);
}
