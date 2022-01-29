#ifndef BleepingLibrary_H
#define BleepingLibrary_H

#include <Arduino.h>

#include "BleepingConfig.h"
#include "BleepingServer.h"
#include "BleepingUUID.h"
#include "BleepingDefinitions.h"

class BleepingLibrary {
  private:
    int setupTimeout;
    BleepingConfig* conf;

  public:
    BleepingLibrary();
    int init();
    BleepingConfig* getConfig();
    boolean beginSetup(int timeout = 90000);
};

#endif
