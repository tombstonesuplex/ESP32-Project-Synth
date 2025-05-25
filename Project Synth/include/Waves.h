#ifndef WAVES_H
#define WAVES_H

#include <string>
#include <cmath>  // for sin()

// Define M_PI if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

enum WaveType {
    SINE,
    SQUARE,
    TRIANGLE,
    SAWTOOTH
};

class Wave {
    private:
        float amplitude = 1.0f;
        float frequency;
        WaveType waveform;

    public:
        // Constructor
        Wave(float frequency = 440.0f, WaveType waveform = SINE);

        float get_amplitude();
        void set_amplitude(float amplitude);

        float get_frequency();
        void set_frequency(float frequency);

        WaveType get_wave_type();
        void set_wave_type(WaveType waveform);

        float get_signal_value(float phase);
};

#endif // WAVES_H
