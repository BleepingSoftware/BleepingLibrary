#ifndef BleepingUUID_H
#define BleepingUUID_H

#include <Arduino.h>

#include "BleepingDefinitions.h"

class BleepingUUID {
  private:
    String uuidString;
  public:
    BleepingUUID(BleepingSystem obj, int opt = 0);
    BleepingUUID(BleepingProperty obj, int opt = 0);
    String toString();
};

#endif
