#ifndef ADSR_H
#define ADSR_H

class ADSREnvelope {
public:
    // Constructor with parameters
    ADSREnvelope(float attack, float decay, float sustain, float release);
    
    // Default constructor
    ADSREnvelope();
    
    // Get the current amplitude based on timing
    float get_amplitude(float timeSincePressed, bool isNoteOn, float timeSinceReleased);
    
    // Public member variables for easy access
    float attack;   // Time in seconds for attack phase
    float decay;    // Time in seconds for decay phase
    float sustain;  // Level (0-1) for sustain phase
    float release;  // Time in seconds for release phase
};

#endif // ADSR_H 