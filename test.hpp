#include "engine.hpp"


void 
testcase() {
    using namespace acc;
    
    try {
        std::string port = "/dev/tty.usbserial-A504DRSI";

        // Create an Engine with a SerialBus.
        // The init arguments are the SerialBus
        // args. *ae* is a pointer to the singleton
        // instance of Engine.
        auto ae = &Engine<SerialBus>::init(port, SerialBus::def_baud());

        // How to access to the bus [Example, not needed].
        ae->bus()->def_port_settings.c_oflag = 0;

        // Set a workload packet.
        ae->set_packet(new Packet);
        // Start the transmission.
        ae->start();

        // If we don't sleep, the function returns
        // without waiting the callbacks. [TEMP] 
        sleep(1);

    } catch (std::runtime_error e) {
        std::cout << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "!!! Unexpected error !!!" << std::endl;
    }
}