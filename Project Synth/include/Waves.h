#ifndef WAVE_H
#define WAVE_H

#include <string>
#include <stdexcept>
#include <cmath>  // for sin()

// Define M_PI if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

enum class WaveTypes { Sine, Sawtooth, Triangular, Square };

// Converts string to WaveTypes enum; throws if invalid string
WaveTypes str_to_wave(const std::string& s);

class Wave {
    private:
        float amplitude;
        float phase;
        float frequency;
        WaveTypes wave_type;

    public:
        Wave(float amplitude, float phase, float frequency, const std::string& wave_type_str);

        float get_amplitude();
        void set_amplitude(float amplitude);

        float get_phase();
        void set_phase(float phase);

        float get_frequency();
        void set_frequency(float frequency);

        WaveTypes get_wave_type();
        void set_wave_type(const std::string& wave_type_str);

        float get_signal_value(float phase);

    private:
        float sine_wave(float phase);
        float square_wave(float phase);
        float sawtooth_wave(float phase);
        float triangular_wave(float phase);
};

class CarrierWave : public Wave {
    private:
        float modulator_index;
    public:
        CarrierWave(float amplitude, float phase, float frequency, const std::string& wave_type_str, float modulator_index);
        float get_modulator_index();
        void set_modulator_index(float modulator_index);
};


#endif // WAVE_H
