# Getting Started

The BleepingLibrary is based around the NVS partition in flash, exposing various configuration parameters through a BLE configuration server when in Setup mode.

The configuration characteristics which can be read / written by another BLE device will allow an end-user to provision and configure their device, making connecting to WiFi network easier then ever.

## Examples

The following examples will start a BLE setup server allowing a user to configure WiFi credentials and more.

### BleepingExample

Once the device has been configured and rebooted, this example will connect to WiFi and then be ready to serve your application.

[Example Sketch](examples/BleepingExample/BleepingExample.ino)

### BleepingUpdate

Once the device has been configured and rebooted, this example will connect to WiFi to download and install a new firmware binary.

[Example Sketch](examples/BleepingUpdate/BleepingUpdate.ino)

## BLE Parameters

A list of all parameters can be found in [BleepingDefinitions.h](src/BleepingDefinitions.h).

### System Parameters

System parameters have a special callback which allow then to interact with the running system.

UUID|Parameter|Mode
---|---|---
00000000-0000-beef-001f-320101000000|Device MAC|R
00000000-0000-beef-001f-32F902000000|Restart Device|W
00000000-0000-beef-001f-32FE02000000|Reset Device|W

### Property Parameters

Property callbacks are configuration parameters which are stored in NVS.

UUID|Parameter|Mode
---|---|---
00000000-0000-beef-001f-320803000000|Device Name|RW
00000000-0000-beef-001f-400203000000|Network Name|RW
00000000-0000-beef-001f-400302000000|Network Password|W
