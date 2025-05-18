#ifndef WAVES_H
#define WAVES_H

#include <string>

enum class WaveTypes { Sine, Sawtooth, Triangular, Square };

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


#endif // WAVES_H
