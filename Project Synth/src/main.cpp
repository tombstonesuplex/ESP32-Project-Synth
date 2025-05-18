#include <Arduino.h>

#include <Waves.h>

// put function declarations here:
int myFunction(int, int);

// can only run in three scenarios:
    // 1. Power on -> Cold Boot from ROM loads firmware from external SPI flash
    // 2. Reset by pressing EN/RST button or ESP.restart() -> Warm Boot from ROM loads firmware from external SPI flash
    // 3. After uploading new firmware -> bootloader auto-resets ESP32 to run new firmware from external SPI flash
void setup() {
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

