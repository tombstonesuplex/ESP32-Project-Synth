#ifndef NOTES_H
#define NOTES_H

#include <Arduino.h>
#include <vector>
#include <stdexcept>

struct ADSREnvelope {
    float attack   = 0.01f;  // seconds
    float decay    = 0.05f;
    float sustain  = 0.8f;   // 0–1
    float release  = 0.08f;
};

// TODO: pitch envelope (i.e for kick drum) ?? 

enum Note {
    // note = semitone
    C = 0,
    Cs = 1,
    D = 2,
    Ds = 3,
    E = 4,
    F = 5,
    Fs = 6,
    G = 7,
    Gs = 8,
    A = 9,
    As = 10,
    B = 11
    // TODO: add C-high
};

float note_frequency(Note note, int octave);

class Scale {
public:
    Note tonic;
    std::vector<int> semitones;
    std::vector<int> semitonePattern;
    std::vector<float> noteFrequencies;
    int tonicOctave;

    Scale(Note tonic, int tonicOctave = 1);

    void generateFrequencies();

    void minusOctave();

    void addOctave();
};

class MajorScale : public Scale {
private:
    const std::vector<int> semitonePattern {0, 2, 4, 5, 7, 9, 11};
public:
    MajorScale(Note tonic, int tonicOctave = 1);
};

class MinorScale : public Scale {
private:
    const std::vector<int> semitonePattern {0, 2, 3, 5, 7, 8, 10};
public:
    MinorScale(Note tonic, int tonicOctave = 1);
};

class PentatonicMajorScale : public Scale {
private:
    const std::vector<int> semitonePattern 	{0, 2, 4, 7, 9};
public:
    PentatonicMajorScale(Note tonic, int tonicOctave = 1);
};

class PentatonicMinorScale : public Scale {
private:
    const std::vector<int> semitonePattern 	{0, 3, 5, 7, 10};
public:
    PentatonicMinorScale(Note tonic, int tonicOctave = 1);
};

class BluesScale : public Scale {
private:
    const std::vector<int> semitonePattern 	{0, 3, 5, 6, 7, 10};
public:
    BluesScale(Note tonic, int tonicOctave = 1);
};

#endif // NOTES_H
