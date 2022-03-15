/**
   BleepingLibrary!
   MClarkDev.com, 2022
   BleepingLibrary.cpp
*/

#include "BleepingLibrary.h"

BleepingLibrary::BleepingLibrary() {
}

/**
   Initialize the library, returns the boot count.
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
   Allows direct access to the BleepingConfig object.
*/
BleepingConfig* BleepingLibrary::getConfig() {
  return this->conf;
}

/**
   Allows direct access to the BleepingServer object.
*/
BleepingServer* BleepingLibrary::getServer() {
  return this->server;
}

String BleepingLibrary::getString(BleepingProperty prop) {
  return conf->getString(BleepingUUID(prop));
}

boolean BleepingLibrary::isConfigured() {
  return conf->getString(BleepingProperty::HardwareConfigured, "0").toInt() > 0;
}

boolean BleepingLibrary::beginSetup(int timeout) {
  return beginSetup(timeout, getString(BleepingProperty::HardwareName).c_str());
}

/**
   Launch the BLE setup server.
*/
boolean BleepingLibrary::beginSetup(int timeout, const char* name) {
  ESP_LOGD(_BLib, "Beginning setup mode.");

  server->setDeviceName(name);
  server->startServer();

  int timeEnd = millis() + timeout;
  while (millis() < timeEnd) {}
  return isConfigured();
}

void BleepingLibrary::enableUpdater(const char* app, int ver) {
  updater = new BleepingUpdater(conf, app, ver);
}

void BleepingLibrary::enableUpdateManager() {
  server->startFirmwareManagerService(updater);
}

BleepingUpdater* BleepingLibrary::getUpdater() {
  return updater;
}
