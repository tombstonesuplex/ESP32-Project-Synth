#ifndef AUDIOPIPELINE_H
#define AUDIOPIPELINE_H

#include <string>     // just in case, for Wave or Notes dependencies
#include <cmath>      // for math constants and functions

#include <Waves.h>    // assuming Wave is defined here
#include <Notes.h>



class AudioPipeline {
private:
    Wave carrier;
    Wave modulator;
    float carrierFrequency = 440.0f;
    float modulatorFrequency = 0.0f;
    float modulatorIndex = 0.0f;
    float sampleRate;
    float phase = 0.0f;

public:
    // Constructor
    AudioPipeline(float sampleRate);

    // Set carrier wave
    void set_carrier(Wave wave);

    // Set modulator wave
    void set_modulator(Wave wave);

    // Set FM synthesis parameters
    void set_fm_parameters(float carrierFreq, float modFreq, float modIndex);

    // Generate audio samples into buffer, returns bytes written
    int32_t generate_audio(uint8_t* data, int32_t byteCount);
};

#endif // AUDIOPIPELINE_H
