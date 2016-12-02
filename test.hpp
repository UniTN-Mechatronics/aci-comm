#include "engine.hpp"

void 
testcase() {
    try {
        
        // Create serial bus
        acc::SerialBus bus("/dev/tty.usbserial-A504DRSI");
        bus.set_baud(B57600);

        // Create a packet
        acc::Packet pck;

        // Create singleton instace of engine
        acc::Engine* ae = &acc::Engine::init(&bus);
        ae->packet = &pck;
        ae->start();

        // If we don't sleep, the function returns
        // without waiting the callbacks. [TEMP] 
        sleep(4);

    } catch (std::runtime_error e) {
        std::cout << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "!!! Unexpected error !!!" << std::endl;
    }
}