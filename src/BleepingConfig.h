#ifndef BleepingConfig_H
#define BleepingConfig_H

#include <Arduino.h>

#include <nvs_flash.h>
#include <Preferences.h>

#include "BleepingDefinitions.h"
#include "BleepingUUID.h"

class BleepingConfig {

  private:
    Preferences* conf;

  public:
    BleepingConfig();
    boolean init();
    void formatAndReboot();
    int getBootCycles();
    String getString(BleepingUUID uuid);
    void putString(BleepingUUID uuid, const char* val);
};

#endif
