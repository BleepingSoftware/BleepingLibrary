# Bleeping Software

Provisioning your IoT devices should not be such a complex process, that's why we built Bleeping Software!

Looking for the [**Device Provisiong Tool**](https://provision.bleepingsoftware.com)?

A universal provisioning and configuration utility for ESP32 applications, our Bleeping Library is a minimal set of utilities built on top of the existing BLE stack combined with the use of non-volatile storage. When paired with our [Open-Source Flutter App](), deploying your ESP32 apps has never been easier!

Visit us online at [BleepingSoftware.com](https://www.bleepingsoftware.com/) for more information!

## BleepingLibrary

Designed to be the configuration store for your ESP32 application, the BleepingLibrary should be loaded when the device first boots, and if required, launch into setup and provisioning mode.

Read the [Getting Started](GettingStarted.md) guide for more information.

### Features

- Provisioning and Configuration
- Basic Device Control and Information
- Custom Configuration BLE Handlers
- OTA Firmware Updates

#### Provisioning Mode

When in setup mode, the BLE server exposes a number of characteristics which can be used be an end-user application to provision and configure a new device.

- Get device MAC
- Get / Set device name
- Set WiFi connection parameters
- Reboot device
- Factory reset device

#### Custom Configuration & Handlers

Built to be customized to meet the needs of any application, the BleepingLibrary allows you to add your own BLE configuration keys or even add your own event handlers.

#### OTA Firmware Updates

Also exposed both through the BLE update server, and to the application, is the ability to preform an OTA firmware upgrade.

This allows applications to periodically check for firmware updates from the server, or update when initiated by the user.

