#include "BleepingUUID.h"

BleepingUUID::BleepingUUID(const char* uuid) {
  this->uuidString = String(uuid);
}

BleepingUUID::BleepingUUID(BleepingSystem obj, int opt) {
  char uuid[37];
  sprintf(uuid, _BLibSystemUUID, obj, opt);
  this->uuidString = String(uuid);
}

BleepingUUID::BleepingUUID(BleepingProperty obj, int opt) {
  char uuid[37];
  sprintf(uuid, _BLibPropertyUUID, obj, opt);
  this->uuidString = String(uuid);
}

String BleepingUUID::toString() {
  return uuidString;
}
