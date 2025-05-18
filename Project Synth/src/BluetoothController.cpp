#include <AudioPipeline.h>
#include <BluetoothA2DPSource.h>
#include <Waves.h>

class BluetoothController {
    private:
        BluetoothA2DPSource bluetoothMaster;
        std::string bluetoothDevice;
    public:
        // init
        BluetoothController(const std::string& bluetoothDevice) {
            this->bluetoothDevice = bluetoothDevice;
        }
        
        void setup() {
            // tells ESP32-A2DB library to call 'get_sound_data' when it needs more audio samples
            bluetoothMaster.set_data_callback(get_sound_data);
            
            // powers up bluetooth controller + names itself master Project Synth
            bluetoothMaster.start("Tronsmart Trip");
        };

        void set_wave();
        
        
        void stop();

};