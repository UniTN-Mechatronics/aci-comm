#include "engine.hpp"


void 
testcase() {
    using namespace acc;
    
    try {
        
        std::string port = "/dev/tty.usbserial-A504DRSI";

        auto ae = &Engine<SerialBus>::init(port, -1);
        ae->set_packet(new Packet);
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