#include "engine.hpp"


void 
testcase() {
    try {
        using namespace acc;
        std::string port = "/dev/tty.usbserial-A504DRSI";

        // Create singleton instance of Engine,
        // and set SerialBus and Packet.
        Engine* ae = &Engine::init(new SerialBus(port), new Packet);
        
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