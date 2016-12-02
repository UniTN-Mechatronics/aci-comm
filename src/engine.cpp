#include "engine.hpp"
#include "commons.hpp"


acc::Engine& 
acc::Engine::create(Bus *bus_) {
    static acc::Engine instance(bus_);
    return instance;
}

void acc::Engine::test() {
    aciInit();
    bus->open();
    std::cout << "Opening bus" << std::endl;
}