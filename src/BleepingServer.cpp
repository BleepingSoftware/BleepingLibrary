/**
   BleepingLibrary!
   MClarkDev.com, 2022
   BleepingServer.cpp
*/

#include "BleepingServer.h"

BleepingServer::BleepingServer(BleepingConfig* conf) {
  this->conf = conf;
  this->deviceName = _BLib;
  this->bleepingUpdater = new BleepingUpdater(conf);
}

void BleepingServer::setDeviceName(const char* deviceName) {
  this->deviceName = deviceName;
}

BleepingUpdater* BleepingServer::getUpdater() {
  return bleepingUpdater;
}

void BleepingServer::startServer() {

  BLEDevice::init(deviceName);
  bleServer = BLEDevice::createServer();
  bleServer->setCallbacks(this);
  BLEService *pService;

  systemCallback = new BleepingSystemCallback(conf);
  propertyCallback = new BleepingPropertyCallback(conf);

  //
  // System Service
  //
  pService = bleServer->createService(BLEUUID(BleepingUUID(BleepingSystem::HARDWARE).toString().c_str()), 12);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareMAC), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareUptime), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareSDK), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareRestart), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareReset), systemCallback);
  pService->start();

  //
  // Firmware Update Service
  //
  pService = bleServer->createService(BLEUUID(BleepingUUID(BleepingSystem::UPDATE).toString().c_str()), 10);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::UpdatePerform), bleepingUpdater);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::UpdateCurrent), bleepingUpdater);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::UpdateLatest), bleepingUpdater);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::UpdateTarget), propertyCallback);
  pService->start();


  //
  // Config Service
  //
  pService = bleServer->createService(BLEUUID(BleepingUUID(BleepingProperty::HARDWARE).toString().c_str()), 8);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::HardwareName), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::HardwareConfigured), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::HardwareBoots), propertyCallback);
  pService->start();

  pService = bleServer->createService(BLEUUID(BleepingUUID(BleepingProperty::NETWORK).toString().c_str()), 6);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::NetworkName), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::NetworkPassword), propertyCallback);
  pService->start();

  pService = bleServer->createService(BLEUUID(BleepingUUID(BleepingProperty::CUSTOM).toString().c_str()), 8);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::Custom00), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::Custom01), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::Custom02), propertyCallback);
  pService->start();


  //
  // Advertising
  //
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BleepingUUID(BleepingSystem::HARDWARE).toString().c_str());
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

BLECharacteristic* BleepingServer::createCharacteristic(BLEService *svc, BleepingUUID uuid, BLECharacteristicCallbacks* callback) {

  const char* uuidStr = uuid.toString().c_str();
  BLECharacteristic *characteristic = svc->createCharacteristic(uuidStr, ((int)uuidStr[29] - '0'));
  characteristic->setCallbacks(callback);
  return characteristic;
}

void BleepingServer::onConnect(BLEServer* pServer) {

  ESP_LOGD(_BLib, "Device connected.");
}

void BleepingServer::onDisconnect(BLEServer* pServer) {

  ESP_LOGD(_BLib, "Device disconnected.");
  BLEDevice::startAdvertising();
}
