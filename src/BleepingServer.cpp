/**
   BleepingLibrary!
   MClarkDev.com, 2022
   BleepingServer.cpp
*/

#include "BleepingServer.h"

BleepingServer::BleepingServer(BleepingConfig* conf) {
  this->conf = conf;

  this->deviceName = _BLib;
  this->customConfig = false;
}

void BleepingServer::setDeviceName(const char* deviceName) {
  this->deviceName = deviceName;
}

void BleepingServer::startServer() {

  // Setup BLE stack
  BLEDevice::init(deviceName);
  bleServer = BLEDevice::createServer();
  bleServer->setCallbacks(this);
  BLEService *pService;

  // Setup Callbacks
  systemCallback = new BleepingSystemCallback(conf);
  propertyCallback = new BleepingPropertyCallback(conf);

  //
  // Advertising
  //
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BleepingUUID(BleepingSystem::HARDWARE).toString().c_str());
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  // System Service
  pService = createService(BleepingUUID(BleepingSystem::HARDWARE), 12);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareMAC), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareUptime), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareRestart), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareReset), systemCallback);
  pService->start();

  // Config Service
  pService = createService(BleepingUUID(BleepingProperty::HARDWARE), 8);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::HardwareName), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::HardwareConfigured), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::HardwareBoots), propertyCallback);
  pService->start();

  // Network Config Service
  pService = createService(BleepingUUID(BleepingProperty::NETWORK), 6);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::NetworkName), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::NetworkPassword), propertyCallback);
  pService->start();
}

BLEService* BleepingServer::createService(BleepingUUID uuid, int numHandles) {

  return bleServer->createService(BLEUUID(uuid.toString().c_str()), numHandles);
}

BLECharacteristic* BleepingServer::createCharacteristic(BLEService *svc, BleepingUUID uuid, BLECharacteristicCallbacks* callback) {

  const char* uuidStr = uuid.toString().c_str();
  BLECharacteristic *characteristic = svc->createCharacteristic(uuidStr, ((int)uuidStr[29] - '0'));
  characteristic->setCallbacks(callback);
  return characteristic;
}

void BleepingServer::startCustomPropertyService(BleepingUUID props[], int numProps) {

  int handles = 2 + (numProps * 2);
  BLEService* s = createService(BleepingUUID(BleepingProperty::CONFIG), handles);

  for(int x = 0; x < numProps; x++) {
    createCharacteristic(s, props[x], propertyCallback);
  }

  s->start();
}

void BleepingServer::startFirmwareManagerService(BleepingUpdater* updater) {

  // Firmware Update Service
  BLEService* s = createService(BleepingUUID(BleepingSystem::FIRMWARE), 12);
  createCharacteristic(s, BleepingUUID(BleepingSystem::FirmwareUpdate), updater);
  createCharacteristic(s, BleepingUUID(BleepingSystem::FirmwareCurrent), updater);
  createCharacteristic(s, BleepingUUID(BleepingSystem::FirmwareLatest), updater);
  createCharacteristic(s, BleepingUUID(BleepingSystem::FirmwareSDK), updater);
  s->start();
}

void BleepingServer::onConnect(BLEServer* pServer) {

  ESP_LOGD(_BLib, "Device connected.");
}

void BleepingServer::onDisconnect(BLEServer* pServer) {

  ESP_LOGD(_BLib, "Device disconnected.");
  BLEDevice::startAdvertising();
}
