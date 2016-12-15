#include "engine.hpp"
#include "aci_comm_uav.hpp"

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
        ae->start(1000, 100);

        // For each key_write, write the
        // specified value.
        ae->write(Cmd::ctrl_mode,                    0);
        ae->write(Cmd::ctrl_enabled,                 1);
        ae->write(Cmd::disable_motor_onoff_by_stick, 1);

        sleep(5);
        std::cout << "READY TO ACC" << std::endl;
        ae->write(Cmd::DIMC_motor_1, 10);
        std::cout << "ACC" << std::endl;
        sleep(2);
        
        /*int i = 0;
        while(i < 1000) {
            // auto yaw = uav.attitude.yaw.read();
            // auto pitch = uav.attitude.pitch.read();
            // auto roll = uav.attitude.roll.read();
            
            // std::cout << yaw << " " << pitch << " " << roll << std::endl;
            //ae->write(Cmd::DIMC_motor_1, 10);

            i++;
            usleep(10000);
        }*/
        std::cout << "READY TO STOP" << std::endl;
        ae->write(Cmd::DIMC_motor_1, 0);
        //usleep(1000);
        //std::cout << "STOP" << std::endl;
        //sleep(5);

    } catch (std::runtime_error e) {
        std::cout << "Exception: " << e.what() << std::endl;
        ae->stop();
    } catch (...) {
        std::cout << "!!! Unexpected error !!!" << std::endl;
        ae->stop();
    }
}

void
testcase2() {
    using namespace acc;
    std::string port = "/dev/tty.usbserial-A504DRSI";

    UAV uav(port, B57600, CTRL_MODE::DIMC);
    try {
        // Enable
        //auto pitch = uav.angles.pitch;
        //pitch.enable_read(0).enable_write(0);

        //uav.angles.pitch.enable_write(0).enable_read(0);
        // uav.attitude.yaw.enable_read(0);
        // uav.attitude.pitch.enable_read(0);
        // uav.attitude.roll.enable_read(0);
        uav.motors[0].enable_read(0);
        uav.motors[0].enable_write(0);
        uav.start();

        uav.control_enable(true);
    
        // Write
        //uav.angles.pitch.write(30.0);
        //uav.angles.roll.write(30.0);
        sleep(5);
        std::cout << "READY" << std::endl;
        // Read
        int i = 0;
        while(i < 1000) {
            // auto yaw = uav.attitude.yaw.read();
            // auto pitch = uav.attitude.pitch.read();
            // auto roll = uav.attitude.roll.read();
            uav.motors[0].write(1500);
            // std::cout << yaw << " " << pitch << " " << roll << std::endl;


            i++;
            usleep(10000);
        }
        uav.motors[0].write(1075);
        sleep(1);

    } catch (std::runtime_error e) {
        std::cout << "Exception: " << e.what() << std::endl;
        uav.stop();
    } catch (...) {
        std::cout << "!!! Unexpected error !!!" << std::endl;
        uav.stop();
    }
}

void
testcase_loop() {
    using namespace acc;
    std::string port = "/dev/tty.usbserial-A504DRSI";
    UAV uav(port, B57600, CTRL_MODE::DIMC);
    
    try {
        uav.motors[0].enable_read(0);
        uav.motors[0].enable_write(0);
        

        
    } catch (std::runtime_error e) {
        std::cout << "Exception: " << e.what() << std::endl;
        uav.stop();
    } catch (...) {
        std::cout << "!!! Unexpected error !!!" << std::endl;
        uav.stop();
    }
}


