#include <vector>
#include <string>
#include <stdexcept>
#include <math.h>

namespace ProjectSynth::Waves {

    // declaring possible wavetypes + mapping them to their string names
    enum class WaveTypes { Sine, Sawtooth, Triangular, Square };
    inline WaveTypes strToWave(const std::string& s) {
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
            WaveTypes waveType;
    
        public:
            Wave(float amplitude, float phase, float frequency, const std::string& waveTypeStr) {
                this->amplitude = amplitude;
                this->phase = phase;
                this->frequency = frequency;
                this->waveType  = strToWave(waveTypeStr);             
            };

            // getters and setters
            float getAmplitude() { return this->amplitude; }
            void setAmplitude(float amplitude) { this->amplitude = amplitude; }

            float getPhase() { return this->phase; }
            void setPhase(float phase) { this->phase = phase; }

            float getFrequency() { return this->frequency; }
            void setFrequency(float frequency) { this->frequency = frequency; }

            WaveTypes getWaveType() { return this->waveType; }
            void setWaveType(const std::string& waveTypeStr) { this->waveType = strToWave(waveTypeStr); }

            float getSignalValue(float phase) {
                switch(waveType) {
                    case WaveTypes::Sine: return sineWave(phase);
                    case WaveTypes::Square: return squareWave(phase); 
                    case WaveTypes::Sawtooth: return sawtoothWave(phase); 
                    case WaveTypes::Triangular: return triangularWave(phase); 
                }
            }

            float sineWave(float phase) {
                return amplitude * sin(phase * 2 * M_PI);
            }

            float squareWave(float phase) {
                if (phase < 0.5f) { return amplitude; } 
                else { return -amplitude; }
            }

            float sawtoothWave(float phase) {
                return (2.0f * amplitude * phase) - amplitude;
            }

            float triangularWave(float phase) {
                if (phase < 0.5f) {
                    // Rising edge from -amplitude to +amplitude
                    return 4.0f * amplitude * phase - amplitude;
                } else {
                    // Falling edge from +amplitude back to -amplitude
                    return -4.0f * amplitude * (phase - 0.5f) + amplitude;
                }
            }
    };

    class CarrierWave : Wave {
        private:
            float modulatorIndex;
        public:
            CarrierWave(float amplitude, float phase, float frequency, const std::string& waveTypeStr, float modulatorIndex)
                : Wave(amplitude, phase, frequency, waveTypeStr), modulatorIndex(modulatorIndex) {}

        
            float getModulatorIndex() { return modulatorIndex; }
            void setModulatorIndex(float modulatorIndex) { this->modulatorIndex = modulatorIndex; }
    };


}
