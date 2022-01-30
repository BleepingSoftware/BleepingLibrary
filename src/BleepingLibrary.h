#ifndef BleepingLibrary_H
#define BleepingLibrary_H

#include <Arduino.h>

#include "BleepingConfig.h"
#include "BleepingServer.h"
#include "BleepingUpdater.h"
#include "BleepingUUID.h"
#include "BleepingDefinitions.h"

class BleepingLibrary {
  private:
    int setupTimeout;
    BleepingConfig* conf;
    BleepingServer* server;

  public:
    BleepingLibrary();
    int init();
    BleepingConfig* getConfig();
    boolean beginSetup(int timeout = 90000);
    String getString(BleepingProperty prop);
    BleepingServer* getServer();
    BleepingUpdater* getUpdater();
    boolean isConfigured();
};

#endif
