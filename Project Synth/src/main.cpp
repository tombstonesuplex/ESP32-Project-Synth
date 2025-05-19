#include <Arduino.h>
#include <BluetoothA2DPSource.h>
#include <AudioTools.h>

#include <Waves.h>
#include <AudioPipeline.h>
#include <BluetoothController.h>
#include <Notes.h>  // for MajorScale and Note

AudioPipeline audioPipeline(44100);  // standard sample rate
int32_t audio_callback(uint8_t* data, int32_t byteCount) {
    return audioPipeline.generate_audio(data, byteCount);
}

BluetoothA2DPSource bluetoothMaster;

// can only run in three scenarios:
    // 1. Power on -> Cold Boot from ROM loads firmware from external SPI flash
    // 2. Reset by pressing EN/RST button or ESP.restart() -> Warm Boot from ROM loads firmware from external SPI flash
    // 3. After uploading new firmware -> bootloader auto-resets ESP32 to run new firmware from external SPI flash
// Declare usbcController globally so it is accessible in both setup() and loop()

// C major scale, octave 4
MajorScale cMajor(Note::C, 4);
unsigned long noteDurationMs = 500;  // 0.5 seconds per note
unsigned long lastNoteChangeTime = 0;
int currentNoteIndex = 0;



void setup() {

    Serial.begin(115200);

    // Initialize scale frequencies (done by constructor and generateFrequencies)
    cMajor.generateFrequencies();

    // Initialize AudioPipeline with first note frequency from C major scale
    float freq = cMajor.noteFrequencies[0];
    audioPipeline.set_carrier(Wave(1.0f, 0.0f, freq, "sine"));
    audioPipeline.set_fm_parameters(freq, 0.0f, 0.0f);

    // sets up the audio pipeline via ESP32-A2DP and Audio Tools Libraries
    bluetoothMaster.start("Tronsmart Trip");
    bluetoothMaster.set_data_callback(audio_callback);

    lastNoteChangeTime = millis();
}

void loop() {

    unsigned long currentTime = millis();

    // change note every 0.5 seconds
    if (currentTime - lastNoteChangeTime >= noteDurationMs) {
        currentNoteIndex = (currentNoteIndex + 1) % cMajor.noteFrequencies.size();
        float freq = cMajor.noteFrequencies[currentNoteIndex];
        Serial.print("Playing note frequency: ");
        Serial.println(freq);

        // update AudioPipeline frequency for the new note
        audioPipeline.set_fm_parameters(freq, 0.0f, 0.0f);
        audioPipeline.set_carrier(Wave(1.0f, 0.0f, freq, "sine"));

        lastNoteChangeTime = currentTime;
    }
}
