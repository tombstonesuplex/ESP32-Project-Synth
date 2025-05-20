#include <math.h>
#include <string>

#include <AudioPipeline.h>


#include <Waves.h>
#include <Notes.h>


AudioPipeline::AudioPipeline(float sampleRate)
    : sampleRate(sampleRate),
    carrier(1.0f, 0.0f, 440.0f, "sine"),    // initialize carrier wave with amplitude=1, phase=0, freq=440Hz, sine wave
    modulator(0.0f, 0.0f, 0.0f, "sine")     // initialize modulator wave as silent (amplitude=0)
{}


void AudioPipeline::set_carrier(Wave wave) { this->carrier = wave; }
void AudioPipeline::set_modulator(Wave wave) { this->modulator = wave; }
void AudioPipeline::set_fm_parameters(float carrierFreq, float modFreq, float modIndex) {
    carrierFrequency = carrierFreq;
    modulatorFrequency = modFreq;
    modulatorIndex = modIndex;
}

    // Generate audio samples
int32_t AudioPipeline::generate_audio(uint8_t* data, int32_t byteCount) {
    int16_t* samples = reinterpret_cast<int16_t*>(data);
    int sampleCount = byteCount / 2;  // 2 bytes per sample

    float phaseIncrement = 2.0f * M_PI * carrierFrequency / sampleRate;

    for (int i = 0; i < sampleCount; ++i) {
        float sample = sin(phase);
        samples[i] = (int16_t)(sample * 32767);
        phase += phaseIncrement;
        if (phase > 2.0f * M_PI) phase -= 2.0f * M_PI;
    }
    return byteCount;
}

// Create a global (or singleton) instance of AudioPipeline


/**********************************************************************
 *  AUDIO PIPELINE — ESP32 → Bluetooth Speaker
 *
 *  1.  Fill a Pulse-Code-Modulation (PCM) buffer        <-- *your part*
 *      • Signed 16-bit little-endian samples
 *      • Sample-Rate and Channel-Count must match what we
 *        declare with set_sample_rate() / set_channels().
 *
 *  2.  Library ring-buffer stores those samples          (ESP32-A2DP)
 *      • Adjustable with set_buffer_len().
 *      • Prevents under-run when callback is a bit late.
 *
 *  3.  SBC encoder compresses each block                 (ESP32-A2DP)
 *      • Transparent to the user; uses default bit-pool.
 *
 *  4.  Bluetooth stack wraps SBC frames into AVDTP/L2CAP (Bluetooth host stack on ESP32)
 *      • Adds media headers and timestamps.
 *      • Also handled automatically.
 *
 *  5.  ESP32 radio transmits packets over 2.4 GHz        (ESP32 bluetooth controller + RF hardware)
 *      • PHY and retransmissions handled by BT controller.
 *
 *  6.  Speaker receives → unwraps → decodes SBC → DAC    (Speaker)
 *      • If steps 1-4 are correct and timely, audio is clean!
 *********************************************************************/

// callback when sample runs out