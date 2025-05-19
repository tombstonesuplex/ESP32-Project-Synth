#include <arduino.h>
#include <vector>
#include <Notes.h>


float note_frequency(Note note, int octave) {
    // start at C1 due to convention
    const float c1Frequency = 32.7;
    const int c1Octave = 1;

    int semitoneFromC1 = (note + (12 * (octave - 1)));
    float frequency = c1Frequency * pow(2.0, semitoneFromC1 / 12.0);
    return frequency;
};


Scale::Scale(Note tonic, int tonicOctave ) : tonic(tonic), tonicOctave(tonicOctave) {}

// Call this after semitones is set to fill noteFrequencies
void Scale::generateFrequencies() {
    noteFrequencies.clear();

    for (int semitoneOffset : semitones) {
        int totalSemitone = static_cast<int>(tonic) + semitoneOffset;
        int noteIndex = totalSemitone % 12;
        int octaveShift = totalSemitone / 12;
        int noteOct = tonicOctave + octaveShift;

        Note note = static_cast<Note>(noteIndex);
        float freq = note_frequency(note, noteOct);
        noteFrequencies.push_back(freq);
    }
}

void Scale::minusOctave() {
    if (tonicOctave == 0) {
        throw std::runtime_error("Octave cannot go below 0");
    }
    else {
        this->tonicOctave -= 1;
        generateFrequencies();
    }
}

void Scale::addOctave() {
    this->tonicOctave += 1;
        generateFrequencies();
}


MajorScale::MajorScale(Note tonic, int tonicOctave)
    : Scale(tonic, tonicOctave)            // call Scale constructor
{
    semitones = semitonePattern;          // copies semitone pattern into semitones (as semitones already initialised in constructor)
    generateFrequencies();                 // fill noteFrequencies
}



MinorScale::MinorScale(Note tonic, int tonicOctave)
    : Scale(tonic, tonicOctave)            // call Scale constructor
{
    semitones = semitonePattern;          // copies semitone pattern into semitones (as semitones already initialised in constructor)
    generateFrequencies();                 // fill noteFrequencies
}
