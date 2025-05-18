#ifndef WAVES_H
#define WAVES_H

#include <string>

namespace ProjectSynth {
namespace Waves {

    enum class WaveTypes { Sine, Sawtooth, Triangular, Square };

    WaveTypes strToWave(const std::string& s);

    class Wave {
        private:
            float amplitude;
            float phase;
            float frequency;
            WaveTypes waveType;
    
        public:
            Wave(float amplitude, float phase, float frequency, const std::string& waveTypeStr);

            float getAmplitude();
            void setAmplitude(float amplitude);

            float getPhase();
            void setPhase(float phase);

            float getFrequency();
            void setFrequency(float frequency);

            WaveTypes getWaveType();
            void setWaveType(const std::string& waveTypeStr);

            float getSignalValue(float phase);

        private:
            float sineWave(float phase);
            float squareWave(float phase);
            float sawtoothWave(float phase);
            float triangularWave(float phase);
    };

    class CarrierWave : public Wave {
        private:
            float modulatorIndex;
        public:
            CarrierWave(float amplitude, float phase, float frequency, const std::string& waveTypeStr, float modulatorIndex);

            float getModulatorIndex();
            void setModulatorIndex(float modulatorIndex);
        };

    } // namespace Waves
} // namespace ProjectSynth

#endif // WAVES_H
