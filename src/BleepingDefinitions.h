/**
   BleepingLibrary!
   MClarkDev.com, 2022
   BleepingDefinitions.h
*/

#ifndef BleepingDefinitions_H
#define BleepingDefinitions_H

#define _BLib "BleepingLibrary"

#define _BLibSystemUUID   "00000000-0000-beef-001f-%06x00%04x"
#define _BLibPropertyUUID "00000000-0000-beef-002f-%06x00%04x"

enum class BleepingSystem {

  HARDWARE = 0x320000,
  HardwareMAC = 0x320101,
  HardwareUptime = 0x320401,
  HardwareRestart = 0x32F902,
  HardwareReset = 0x32FE02,

  FIRMWARE = 0x800000,
  FirmwareUpdate = 0x800102,
  FirmwareCurrent = 0x800201,
  FirmwareLatest = 0x800301,
  FirmwareSDK = 0x808201
};

enum class BleepingProperty {

  HARDWARE = 0x320000,
  HardwareName = 0x320803,
  HardwareConfigured = 0x321203,
  HardwareBoots = 0x32F001,

  NETWORK = 0x400000,
  NetworkName = 0x400203,
  NetworkPassword = 0x400302,

  CONFIG = 0xA00000,
};

#endif
