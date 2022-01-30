#ifndef BleepingCallbacks_H
#define BleepingCallbacks_H

#include <Arduino.h>

#include <BLEDevice.h>

#include <WiFi.h>

#include "BleepingConfig.h"
#include "BleepingDefinitions.h"
#include "BleepingUUID.h"

class BleepingSystemCallback : public BLECharacteristicCallbacks {

  private:
    BleepingConfig* conf;

  public:
    BleepingSystemCallback(BleepingConfig* conf);

  protected:
    void onWrite(BLECharacteristic *pCharacteristic) override;
    void onRead(BLECharacteristic* pCharacteristic) override;
};

class BleepingPropertyCallback : public BLECharacteristicCallbacks {

  private:
    int lastT;
    std::string lastK;
    boolean continued;
    BleepingConfig* conf;

  public:
    BleepingPropertyCallback(BleepingConfig* conf);

  protected:
    void onWrite(BLECharacteristic *characteristic) override;
    void onRead(BLECharacteristic* characteristic) override;
};

#endif
