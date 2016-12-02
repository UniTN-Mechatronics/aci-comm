#include "engine.hpp"

void t() {
    // Create serial bus
    acc::SerialBus bus("portexample");

    // Create singleton instace of engine
    acc::Engine* ae = &acc::Engine::create(&bus);
    ae->test();
    
}