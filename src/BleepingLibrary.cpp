
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

  return conf->getBootCycles();
}

/**
 * Allows access to the BellpingConfig object.
 */
BleepingConfig* BleepingLibrary::getConfig() {
  return this->conf;
}

/**
 * Launch the BLE setup server.
 */
boolean BleepingLibrary::beginSetup(int timeout) {
  ESP_LOGD(_BLib, "Beginning setup mode.");

  BleepingServer* server = new BleepingServer(conf);
  server->setDeviceName("My Bleeping Device");
  server->startServer();

  int timeEnd = millis() + timeout;
  while(millis() < timeEnd) {}
  return conf->isConfigured();
}
