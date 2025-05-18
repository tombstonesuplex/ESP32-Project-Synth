#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H

#include <BluetoothA2DPSource.h>
#include <Waves.h>
#include <string>
#include <AudioPipeline.h>

class BluetoothController
{
private:
    BluetoothA2DPSource bluetooth_master_;   // the ESP32-A2DP object
    std::string         bluetooth_device_;   // friendly name of speaker

public:
    //----------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------
    explicit BluetoothController(const std::string& bluetooth_device)
        : bluetooth_master_{},            // default-construct the source
          bluetooth_device_{bluetooth_device}
    {}

    //----------------------------------------------------------------
    // Bring the A2DP source up and register the audio callback
    //----------------------------------------------------------------
    void setup()
    {
        // register PCM callback declared above
        bluetooth_master_.set_data_callback(get_sound_data);

        // start advertising / auto-connect with given name
        bluetooth_master_.start(bluetooth_device_.c_str());
    }

    //----------------------------------------------------------------
    // Change the generator that fills the PCM buffer (you’ll define it)
    //----------------------------------------------------------------
    void set_wave(const ProjectSynth::Waves::Wave& wave);

    //----------------------------------------------------------------
    // Graceful shutdown
    //----------------------------------------------------------------
    void stop()
    {
        bluetooth_master_.stop();
    }
};

#endif // BLUETOOTH_CONTROLLER_H

#endif // BLUETOOTHCONTROLLER_H
