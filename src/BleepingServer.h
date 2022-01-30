/**
   BleepingLibrary!
   MClarkDev.com, 2022
   BleepingServer.h
*/

#ifndef BleepingServer_H
#define BleepingServer_H

#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "BleepingConfig.h"
#include "BleepingUUID.h"
#include "BleepingDefinitions.h"
#include "BleepingCallbacks.h"
#include "BleepingUpdater.h"

class BleepingServer : public BLEServerCallbacks {

  private:
    BleepingConfig* conf;
    const char* deviceName;
    BLEServer* bleServer;
    BleepingUpdater* bleepingUpdater;
    BleepingSystemCallback* systemCallback;
    BleepingPropertyCallback* propertyCallback;
    BLECharacteristic* createCharacteristic(BLEService *svc, BleepingUUID uuid, BLECharacteristicCallbacks* callback);

  public:
    BleepingServer(BleepingConfig* conf);
    void startServer();
    void setDeviceName(const char* deviceName);
    BleepingUpdater* getUpdater();

  protected:
    void onConnect(BLEServer* pServer) override;
    void onDisconnect(BLEServer* pServer) override;
};

#endif
