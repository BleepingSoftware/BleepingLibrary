/**
   BleepingLibrary!
   MClarkDev.com, 2022
   BleepingUpdater.h
*/

#ifndef BleepingUpdater_H
#define BleepingUpdater_H

#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>

#include <BLEDevice.h>

#include "BleepingConfig.h"

class BleepingUpdater : public BLECharacteristicCallbacks {
  private:
    BleepingConfig* conf;
    WiFiClient client;
    const char* app;
    int ver;
    String fetch(String url);

  public:
    BleepingUpdater(BleepingConfig* conf, const char* app, int ver);
    boolean connect();
    boolean checkUpdateAvailable();
    boolean doUpdate();
    boolean doUpdate(const char* target);

  protected:
    void onWrite(BLECharacteristic *characteristic) override;
    void onRead(BLECharacteristic* characteristic) override;
};

#endif
