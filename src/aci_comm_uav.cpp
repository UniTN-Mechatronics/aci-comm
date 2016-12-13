#include "aci_comm_uav.hpp"


void 
acc::UAV::set_port(std::string port_id) {
	ae->bus()->set_port(port_id);
}

void 
acc::UAV::start() {
	ae->start();
}

void 
acc::UAV::stop() {
	ae->stop();
}
