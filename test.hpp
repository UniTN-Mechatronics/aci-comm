#include "engine.hpp"


void 
testcase() {
    using namespace acc;
    Engine<SerialBus>* ae;

    try {
        std::string port = "/dev/tty.usbserial-A504DRSI";
        //std::string port = "/dev/tty.usbserial-AL00XNUW";
        
        // Create an Engine with a SerialBus.
        // The init arguments are the SerialBus
        // args. *ae* is a pointer to the singleton
        // instance of Engine.
        ae = &Engine<SerialBus>::init(port, B57600);

        // Add variables to read, to packet 1.
        ae->add_read(0, Var::motor_rpm_1, Var::motor_rpm_2, Var::motor_rpm_3, Var::motor_rpm_4); 
        
        // Add commands to write, packet 0.
        ae->add_write(0, Cmd::DIMC_motor_1,
                         Cmd::DIMC_motor_2,
                         Cmd::DIMC_motor_3,
                         Cmd::DIMC_motor_4,   
                         Cmd::ctrl_mode, 
                         Cmd::ctrl_enabled, 
                         Cmd::disable_motor_onoff_by_stick);


        // Start the engine.
        // Returns when the variables and
        // commands callbacks are executed.
        // Default engine params: 100, 10
        ae->start();

        // For each key_write, write the
        // specified value.
        ae->write(Cmd::ctrl_mode,                    0,
                  Cmd::ctrl_enabled,                 1,
                  Cmd::disable_motor_onoff_by_stick, 1);



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


