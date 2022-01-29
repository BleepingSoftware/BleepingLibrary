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
    String key(const char* uuid);
    String key(BleepingProperty obj);

  public:
    BleepingConfig();
    boolean init();
    void formatAndReboot();
    int getBootCycles();
    boolean isConfigured();
    String getString(const char* name);
    String getString(BleepingProperty name);
    void putString(const char* name, const char* val);
    void putString(BleepingProperty name, const char* val);
};

#endif
