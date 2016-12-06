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
        ae->add_read(1, "motor_rpm_1"); // To packet 0

        // Add commands to write.
        ae->add_write(0, "DIMC_motor_1");
        ae->add_write(0, "ctrl_mode");
        ae->add_write(0, "ctrl_enabled");
        ae->add_write(0, "disable_motor_onoff_by_stick");

        // Start the engine.
        // Returns when the variables and
        // commands callbacks are executed.
        // Default engine params: 100, 10
        ae->start();
        ae->write("ctrl_mode", 0);
        ae->write("ctrl_enabled", 1);
        ae->write("disable_motor_onoff_by_stick", 1);

        int val = 0;
        while(true) {
            std::string cmd;
            std::cout << "Cmd: ";
            std::cin >> cmd;
            if (cmd == "exit") break;
            if (cmd == "?") {
                std::cout << "RPM: " << ae->read("motor_rpm_1") << std::endl;
                continue;
            } else {
                std::cout << "\nVal: ";
                std::cin >> val;
                ae->write("DIMC_motor_1", val); 
            }
        }

    } catch (std::runtime_error e) {
        std::cout << "Exception: " << e.what() << std::endl;
        ae->stop();
    } catch (...) {
        std::cout << "!!! Unexpected error !!!" << std::endl;
        ae->stop();
    }
}
