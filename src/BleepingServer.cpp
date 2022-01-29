#include "BleepingServer.h"

BleepingServer::BleepingServer(BleepingConfig* conf) {
  this->conf = conf;
  this->deviceName = _BLib;

  systemCallback = new BleepingSystemCallback(conf);
  propertyCallback = new BleepingPropertyCallback(conf);
}

void BleepingServer::setDeviceName(const char* deviceName) {
  this->deviceName = deviceName;
}

void BleepingServer::startServer() {

  const char* uuid;
  BLEService *pService;

  int R = BLECharacteristic::PROPERTY_READ;
  int W = BLECharacteristic::PROPERTY_WRITE;

  BLEDevice::init(deviceName);
  bleServer = BLEDevice::createServer();
  bleServer->setCallbacks(this);

  //
  // System Service
  //
  pService = bleServer->createService(BLEUUID(BleepingUUID(BleepingSystem::ROOT).toString().c_str()), 18);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareMAC), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareUptime), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareSDK), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareRestart), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::HardwareReset), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::UpdatePerform), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::UpdateCurrent), systemCallback);
  createCharacteristic(pService, BleepingUUID(BleepingSystem::UpdateLatest), systemCallback);

  pService->start();


  //
  // Config Service
  //
  pService = bleServer->createService(BLEUUID(BleepingUUID(BleepingProperty::ROOT).toString().c_str()), 20);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::HardwareName), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::HardwareConfigured), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::HardwareBoots), propertyCallback);

  createCharacteristic(pService, BleepingUUID(BleepingProperty::NetworkName), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::NetworkPassword), propertyCallback);

  createCharacteristic(pService, BleepingUUID(BleepingProperty::UpdateTarget), propertyCallback);

  createCharacteristic(pService, BleepingUUID(BleepingProperty::Custom00), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::Custom01), propertyCallback);
  createCharacteristic(pService, BleepingUUID(BleepingProperty::Custom02), propertyCallback);

  pService->start();

  //
  // Advertising
  //
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BleepingUUID(BleepingSystem::ROOT).toString().c_str());
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

}

void BleepingServer::onDisconnect(BLEServer* pServer) {
  BLEDevice::startAdvertising();
}
