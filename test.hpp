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
        ae->add_read(0, "RC_channel_0", "angle_roll", "angle_yaw"); // To packet 0
        //ae->add_read(1, "battery_voltage", "Hx", "Hy"); // To packet 0

        // Add commands to write.
        ae->add_write(2, "DIMC_motor_1");
        ae->add_write(2, "ctrl_mode");
        ae->add_write(2, "ctrl_enabled");
        ae->add_write(2, "disable_motor_onoff_by_stick");

        // Start the engine.
        // Returns when the variables and
        // commands callbacks are executed.
        // Default engine params: 100, 10
        ae->start();

        ae->write("ctrl_enabled", 1);
        ae->write("disable_motor_onoff_by_stick", 1);
        int i = 0;
        while(i < 1000) {
            std::cout << "RC_channel_0: " <<  ae->read("RC_channel_0") << std::endl;
            std::cout << "Angle_roll: " <<  ae->read("angle_roll") << std::endl;
            std::cout << "Angle_yaw: " <<  ae->read("angle_yaw") << std::endl;
            /*std::cout << "voltage: " <<  ae->read("battery_voltage") << std::endl;
            std::cout << "Hx: " <<  ae->read("Hx") << std::endl;
            std::cout << "Hy: " <<  ae->read("Hy") << std::endl;*/
            usleep(10000);
            ++i;
        }
        //std::string cmd;
        //int val = 0;
        //while(true) {
        //    std::cout << "Cmd: ";
        //    std::cin >> cmd;
        //    if (cmd == "exit") break;
        //    std::cout << "Val: ";
        //    std::cin >> val;
        //    ae->write("DIMC_motor_1", val);
        //}

    } catch (std::runtime_error e) {
        std::cout << "Exception: " << e.what() << std::endl;
        ae->stop();
    } catch (...) {
        std::cout << "!!! Unexpected error !!!" << std::endl;
        ae->stop();
    }
}

        /*auto vec_results = ae->read("angle_pitch", "angle_roll", "angle_yaw");
            for (auto &r : vec_results)
                std::cout << r << std::endl;*/

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