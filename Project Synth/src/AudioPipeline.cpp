#include <math.h>
#include <string>
#include <Waves.h>

class AudioPipeline {
    private:
        Wave carrier;
        Wave modulator;
        float carrierFrequency;
        float modulatorFrequency;
        float modulatorIndex;

        void set_fm_parameters(float carrierFreq, float modFreq, float modIndex);
    public:
        AudioPipeline(float sampleRate);

        void set_carrier(Wave wave) { this->carrier = wave; }
        void set_modulator(Wave wave) { this->modulator = wave;}
};

// callback when sample runs out
int32_t get_sound_data(uint8_t *data, int32_t byteCount) {
            // generate your sound data 
            // return the effective length in bytes
            return byteCount;
};

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
