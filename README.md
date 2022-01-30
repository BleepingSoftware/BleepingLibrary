# BleepingSoftware

Provisioning and configuring an ESP32 should not be such a complex process, that's why we built Bleeping Software!

With minimal set of funtions on top of the Arduino BLE stack combined with our Flutter app compiled for a number of different devices, provisioning your ESP32 has never been easier.

## BleepingLibrary

Designed to be the configuration store for your ESP32 application, the BleepingLibrary should be loaded when the device first boots, and if required, launch into setup and provisioning mode.

Read the [Getting Started](GettingStarted.md) guide for more information.

### Features

- Provisioning Mode
- Basic Device Control and Information
- Custom Configuration
- Custom BLE Callbacks
- OTA Firmware Updates

## Provisioning Mode

The BLE server exposes a number of characteristics which can be used be an end-user to provision a new device.

- Get device MAC
- Get / Set device name
- Set WiFi connection parameters

## Device Control

The library also exposes simple device control including the ability to preform a 'factory reset'.

- Reboot Device
- Factory Reset Device

## Custom Configuration & Callbacks

Built to be customized to meet the needs of any application, the BleepingLibrary allows you to add your own BLE configuration options.

## OTA Firmware Updates

Also exposed both through the BLE update server, and to the application, is the ability to preform an OTA firmware upgrade.

