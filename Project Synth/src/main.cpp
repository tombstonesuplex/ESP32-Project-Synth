#include <Arduino.h>

#include <Waves.h>
#include <AudioPipeline.h>
#include <BluetoothController.h>

// function declarations
extern void initialiseAudioPipeline();

// var declarations
BluetoothController bluetoothController;

// can only run in three scenarios:
    // 1. Power on -> Cold Boot from ROM loads firmware from external SPI flash
    // 2. Reset by pressing EN/RST button or ESP.restart() -> Warm Boot from ROM loads firmware from external SPI flash
    // 3. After uploading new firmware -> bootloader auto-resets ESP32 to run new firmware from external SPI flash
// Declare usbcController globally so it is accessible in both setup() and loop()
void setup() {

    // sets up the audio pipline via ESP32-A2DB and Audio Tools Libraries
    bluetoothController = BluetoothController("Tronsmart Trip");
    bluetoothController.setup();

}


void loop() {

}

