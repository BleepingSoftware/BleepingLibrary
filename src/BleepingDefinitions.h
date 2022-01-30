#ifndef BleepingDefinitions_H
#define BleepingDefinitions_H

#define _BLib "BleepingLibrary"

#define _BLibSystemUUID   "00000000-0000-beef-001f-%06x00%04x"
#define _BLibPropertyUUID "00000000-0000-beef-002f-%06x00%04x"

enum class BleepingSystem {

  HARDWARE = 0x320000,
  HardwareMAC = 0x320101,
  HardwareUptime = 0x320401,
  HardwareSDK = 0x324201,
  HardwareRestart = 0x32F902,
  HardwareReset = 0x32FE02,

  UPDATE = 0x800000,
  UpdatePerform = 0x800102,
  UpdateCurrent = 0x800201,
  UpdateLatest = 0x800201
};

enum class BleepingProperty {

  HARDWARE = 0x320000,
  HardwareName = 0x320803,
  HardwareConfigured = 0x321203,
  HardwareBoots = 0x32F001,

  UPDATE = 0x800000,
  UpdateTarget = 0x800103,

  NETWORK = 0x400000,
  NetworkName = 0x400203,
  NetworkPassword = 0x400302,

  CUSTOM = 0xA00000,
  Custom00 = 0xA00203,
  Custom01 = 0xA00403,
  Custom02 = 0xA00603
};

#endif
