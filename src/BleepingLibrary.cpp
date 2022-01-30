
#include "BleepingLibrary.h"

BleepingLibrary::BleepingLibrary() {
}

/**
 * Initialize the library, returns the boot count.
 */
int BleepingLibrary::init() {

  conf = new BleepingConfig();
  if (!conf->init()) {
    conf->formatAndReboot();
  }

  server = new BleepingServer(conf);

  return conf->getBootCycles();
}

/**
 * Allows access to the BellpingConfig object.
 */
BleepingConfig* BleepingLibrary::getConfig() {
  return this->conf;
}

BleepingServer* BleepingLibrary::getServer() {
  return this->server;
}

BleepingUpdater* BleepingLibrary::getUpdater() {
  return this->server->getUpdater();
}

String BleepingLibrary::getString(BleepingProperty prop) {
  return conf->getString(BleepingUUID(prop));
}

boolean BleepingLibrary::isConfigured() {
  return getString(BleepingProperty::HardwareConfigured).toInt() > 0;
}

/**
 * Launch the BLE setup server.
 */
boolean BleepingLibrary::beginSetup(int timeout) {
  ESP_LOGD(_BLib, "Beginning setup mode.");


  server->setDeviceName("My Bleeping Device");
  server->startServer();

  int timeEnd = millis() + timeout;
  while(millis() < timeEnd) {}
  return isConfigured();
}
