#include "aci_comm_uav.hpp"


void 
acc::UAV::set_port(std::string port_id) {
	engine->bus()->set_port(port_id);
}

std::string 
acc::UAV::port() {
	return engine->bus()->port();
}

void 
acc::UAV::start() {
	engine->start();
}

void 
acc::UAV::stop() {
	engine->stop();
}
