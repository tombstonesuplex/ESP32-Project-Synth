#ifndef VOICE_H
#define VOICE_H

#include <Waves.h>
#include <ADSR.h>

// TODO: pitch envelope (i.e for kick drum) ?? 

class Voice {
    private:
        float carrierFrequency;
        float modulatorFrequency;
        float modulatorIndex;
        float timePressed;
        float timeDepressed;
        int keyIndex;
        
        // Phase accumulators for oscillators
        float carrierPhase = 0.0f;
        float modulatorPhase = 0.0f;
        
        // ADSR envelope for amplitude modulation
        ADSREnvelope adsrEnvelope;
        
        // Oscillators
        Wave carrierWave = Wave(carrierFrequency, SINE);
        Wave modulatorWave = Wave(modulatorFrequency, SINE);

    public:
        Voice(
            ADSREnvelope adsrEnvelope,
            float carrierFrequency,
            float modulatorFrequency,
            float modulatorIndex,
            float currentAudioTime,
            int keyIndex
        );

        void press_button(float currentAudioTime);
        void depress_button(float currentAudioTime);
        float fm_synthesis(float sampleRate, float currentAudioTime);
        bool is_active(float currentTime);
        int get_key_index();
};

#endif // VOICE_H