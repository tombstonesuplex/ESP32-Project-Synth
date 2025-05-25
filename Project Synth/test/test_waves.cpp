#include <Arduino.h>
#include <unity.h>
#include <Waves.h>

// Declare test functions
void test_invalid_wave_type();
void test_100_sample_signals();

// runs once before test starts
void setup(void) {
    // initialize Unity
    UNITY_BEGIN();  
                 
    RUN_TEST(test_invalid_wave_type);    // Call the test function
    RUN_TEST(test_100_sample_signals);
    // print summary results
    UNITY_END();    
};


// Code here runs before each test
void setUp(void) {
    
}


// Code here runs after each test
void tearDown(void) {
  
}

// test 100 samples from each wave type
void test_100_sample_signals() {
    float signalValue;
    bool invalidSignal = false;

    // for all four wave types, make 100 of them and check their signal between -1 and 1
    for (std::string allowedWave : {"sine", "triangle", "sawtooth", "square"}) {
        for (float i = 0; i < 1.0; i += 0.01) {
            Wave w(7, allowedWave);
            signalValue = w.get_signal_value(i);
            if (signalValue < -1 || signalValue > 1) {
                invalidSignal = true;
                break;
            };
        };
        if (invalidSignal == true) {
            break;
        };
    };
    TEST_ASSERT_FALSE_MESSAGE(invalidSignal, "Signal value out of range -1 to 1 for wave type");
};

// Test that invalid waveType throws std::invalid_argument
void test_invalid_wave_type() {
    bool threw = false;

    try {
        Wave invalidWave(440, "invalid_wave");
    } catch (const std::invalid_argument& e) {
        threw = true;
        TEST_ASSERT_NOT_NULL(e.what());
    }

    TEST_ASSERT_TRUE_MESSAGE(threw, "Expected std::invalid_argument exception was not thrown");
}




