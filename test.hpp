#include "engine.hpp"


void 
testcase() {
    using namespace acc;
    Engine<SerialBus>* ae;

    try {
        std::string port = "/dev/tty.usbserial-A504DRSI";

        // Create an Engine with a SerialBus.
        // The init arguments are the SerialBus
        // args. *ae* is a pointer to the singleton
        // instance of Engine.
        ae = &Engine<SerialBus>::init(port, B57600);

        // Add variables to read.
        ae->add_read(0, "angle_pitch"); // To packet 0
        ae->add_read(1, "Label", "angle_roll", "angle_yaw"); // To packet 1
        
        // Start the engine.
        // Returns when the variables and
        // commands callbacks are executed.
        // Default engine params: 100, 10
        ae->start();

        int i = 0;
        while(i < 1000) {
            /*auto vec_results = ae->read("angle_pitch", "angle_roll", "angle_yaw");
            for (auto &r : vec_results)
                std::cout << r << std::endl;*/

            std::cout << "Angle_pitch: " <<  ae->read("angle_pitch") << std::endl;
            std::cout << "Angle_roll: " <<  ae->read("angle_roll") << std::endl;
            std::cout << "Angle_yaw: " <<  ae->read("angle_yaw") << std::endl;
            usleep(10000);
            ++i;
        }
    } catch (std::runtime_error e) {
        std::cout << "Exception: " << e.what() << std::endl;
        ae->stop();
    } catch (...) {
        std::cout << "!!! Unexpected error !!!" << std::endl;
        ae->stop();
    }
}

     /*ae->add_read(1, "angle_pitch", "angle_roll", "angle_yaw");
        ae->add_def_read(angles);
        ae->add_write(0, "pitch");
        ae->add_def_write(0, thurst);
        // Start the transmission. // Add return only when all is setted
        ae->start();
        sleep(2); // Remove
        auto value_pitch = ae->read("angle_pitch");
        auto values_angle = ae->read(angles.name);
        ae->write_now("pitch", 0.678);
        ae->write(thurst, [0,1,0,1]);
        ae->apply(); // apply the write only commands
        */
        // If we don't sleep, the function returns
        // without waiting the callbacks. [TEMP] 