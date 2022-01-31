# Getting Started

The BleepingLibrary is based around the NVS partition in flash, exposing various configuration parameters through a BLE configuration server when in Setup mode.

The configuration characteristics which can be read / written by another BLE device will allow an end-user to provision and configure their device, making connecting to WiFi network easier then ever.

## Examples

The following examples will start a BLE setup server allowing a user to configure WiFi credentials and more.

### BleepingExample

The [BleepingExample](examples/BleepingExample/BleepingExample.ino) sketch will demonstrate:

- Checking if a device is configured
- Optionally launching setup mode
- Loading WiFi credentials from config

On boot the device will check if it needs to be configured and optionally launch setup mode. Once the user has configured and rebooted the device, this example will connect to WiFi and then be ready to serve your application.

### BleepingUpdate

The [BleepingUpdate](examples/BleepingUpdate/BleepingUpdate.ino) skecth will demonstrate:

- Checking if a device is configured
- Optionally launching setup mode
- Using the BleepingUpdater to download new software

When booted, a configred device will download and install a new firmware image using either the target specified in setup, or the default target.

### BleepingCustomImpl

The [BleepingCustomImpl](examples/BleepingCustomImpl/BleepingCustomImpl.ino) sketch will demonstrate:

- Manually starting the BLE setup server
- Adding a custom service, characteristics, and callback
- Running an application with setup mode in the background

This example will add a custom service and characteristics to the setup server, with a custom callback attached. After starting the BLE setup server, control is returned to the user application.

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
