#include <vector>
#include <string>
#include <stdexcept>
#include <math.h>

enum class WaveTypes { Sine, Sawtooth, Triangular, Square };

inline WaveTypes str_to_wave(const std::string& s) {
    if (s == "sine")        return WaveTypes::Sine;
    if (s == "sawtooth")    return WaveTypes::Sawtooth;
    if (s == "triangular")  return WaveTypes::Triangular;
    if (s == "square")      return WaveTypes::Square;
    throw std::invalid_argument("Unknown wave type: " + s);
};


class Wave {
    private:
        float amplitude;
        float phase;
        float frequency;
        WaveTypes wave_type;

    public:
        Wave(float amplitude, float phase, float frequency, const std::string& wave_type_str) {
            this->amplitude = amplitude;
            this->phase = phase;
            this->frequency = frequency;
            this->wave_type  = str_to_wave(wave_type_str);             
        };

        // getters and setters
        float get_amplitude() { return this->amplitude; }
        void set_amplitude(float amplitude) { this->amplitude = amplitude; }

        float get_phase() { return this->phase; }
        void set_phase(float phase) { this->phase = phase; }

        float get_frequency() { return this->frequency; }
        void set_frequency(float frequency) { this->frequency = frequency; }

        WaveTypes get_wave_type() { return this->wave_type; }
        void set_wave_type(const std::string& wave_type_str) { this->wave_type = str_to_wave(wave_type_str); }

        float get_signal_value(float phase) {
            switch(wave_type) {
                case WaveTypes::Sine: return sine_wave(phase);
                case WaveTypes::Square: return square_wave(phase); 
                case WaveTypes::Sawtooth: return sawtooth_wave(phase); 
                case WaveTypes::Triangular: return triangular_wave(phase); 
            }
            return 0.0f; // avoid warning
        }

        float sine_wave(float phase) {
            return amplitude * sin(phase * 2 * M_PI);
        }

        float square_wave(float phase) {
            if (phase < 0.5f) { return amplitude; } 
            else { return -amplitude; }
        }

        float sawtooth_wave(float phase) {
            return (2.0f * amplitude * phase) - amplitude;
        }

        float triangular_wave(float phase) {
            if (phase < 0.5f) {
                return 4.0f * amplitude * phase - amplitude;
            } else {
                return -4.0f * amplitude * (phase - 0.5f) + amplitude;
            }
        }
};

class CarrierWave : public Wave {
    private:
        float modulator_index;
    public:
        CarrierWave(float amplitude, float phase, float frequency, const std::string& wave_type_str, float modulator_index)
            : Wave(amplitude, phase, frequency, wave_type_str), modulator_index(modulator_index) {}

        float get_modulator_index() { return modulator_index; }
        void set_modulator_index(float modulator_index) { this->modulator_index = modulator_index; }
};
