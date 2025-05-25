#ifndef STATE_H
#define STATE_H

#include <Notes.h>
#include <Voice.h>
#include <ADSR.h>
#include <vector>

// key-independent state
class CurrentState {
    private:
        int sampleRate;
        ADSREnvelope currentADSREnvelope;
        std::vector<int> ledPattern;
        int currentOctave;
        float currentModulatorIndex;
        float modulatorRatio;

        std::vector<Voice> activeVoices;

        std::vector<float> keyboardFrequencies;
        std::vector<float> allFrequencies;
        float audioTime = 0.0f;
    public:
        // static CurrentState& getInstance(int sampleRate = 44100) {
        //     static CurrentState instance(sampleRate);
        //     return instance;
        // }
        
        CurrentState(int sampleRate);
        float get_audio_time() const;
        // setters for button induced state values
        void set_ADSRPreset(ADSREnvelope newADSREnvelope);
        void set_scale(std::vector<int> ledPattern);
        void set_octave(int newOctave);
        // set filter preset?
        // set carrier wave type (e.g sine)?
        // set modulator wave type (e.g sawtooth)?

        // setters for dial-induced state values
        void set_modulatorIndex(float newModulatorIndex);

        void render_keyboard_frequencies();

        void press_key(int keyPressed, float time);
        void depress_key(int keyPressed, float time);

        float render_voices(float time);
        int32_t generate_audio(uint8_t* data, int32_t byteCount);


};

extern const std::vector<int> majorPattern;
extern const std::vector<int> minorPattern;
extern const std::vector<int> pentatonicMajorPattern;
extern const std::vector<int> pentatonicMinorPattern;
extern const std::vector<int> bluesPattern;

#endif // STATE_H
