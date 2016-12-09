#include "engine.hpp"


void 
testcase() {
    using namespace acc;
    using Vars = acc::ACI_COMM_VAR; 
    Engine<SerialBus>* ae;

    try {
        std::string port = "/dev/tty.usbserial-A504DRSI";
        //std::string port = "/dev/tty.usbserial-AL00XNUW";
        
        auto e = Vars::UAV_status;

        // Create an Engine with a SerialBus.
        // The init arguments are the SerialBus
        // args. *ae* is a pointer to the singleton
        // instance of Engine.
        ae = &Engine<SerialBus>::init(port, B57600);

        // Add variables to read, to packet 1.
        ae->add_read(0, "motor_rpm_1", "motor_rpm_2", "motor_rpm_3", "motor_rpm_4"); 

        // Add commands to write, packet 0.
        ae->add_write(0, "DIMC_motor_1",
                         "DIMC_motor_2",
                         "DIMC_motor_3",
                         "DIMC_motor_4",   
                         "ctrl_mode", 
                         "ctrl_enabled", 
                         "disable_motor_onoff_by_stick");

        // Start the engine.
        // Returns when the variables and
        // commands callbacks are executed.
        // Default engine params: 100, 10
        ae->start();

        // For each key_write, write the
        // specified value.
        ae->write("ctrl_mode",                    0,
                  "ctrl_enabled",                 1,
                  "disable_motor_onoff_by_stick", 1);

        // Cycle for control
        // the drone from console input.
        int val = 0;
        while(true) {
            std::string cmd;
            std::cout << "Cmd: ";
            std::cin >> cmd;
            if (cmd == "exit") break;
            if (cmd == "r") {
                auto vec_of_res = ae->read("motor_rpm_1", "motor_rpm_2", "motor_rpm_3", "motor_rpm_4");
                for (int i = 0; i < vec_of_res.size(); ++i) {
                    std::cout << "rpm m" + std::to_string(i) + ": " << vec_of_res[i] << std::endl;
                }
                continue;
            } 
            else {
                std::cout << "\nVal: ";
                std::cin >> val;
                ae->write("DIMC_motor_1", val, "DIMC_motor_2", val, "DIMC_motor_3", val, "DIMC_motor_4", val); 
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


/*
        aciPacket motors_rpm(1, 1000, "motor_rpm_1", "motor_rpm_2", "motor_rpm_3", "motor_rpm_4");

        aciPacket quaternion(2, 1000, "quaternion"); // quaterrnon \in R^4

        motors_rpm[1].read()

        ae->add_read(motors_rpm, quaternion);
        auto rpm = ae->read(motors_rpm);
        ae->read(motors_rpm[1]);*/


