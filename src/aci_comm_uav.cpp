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
  _write_ctrl();
}

void 
acc::UAV::stop() {
	engine->stop();
}

void
acc::UAV::control_enable(bool value) {
  if (_ctrl_mode == CTRL_MODE::READ_ONLY) {
    throw std::runtime_error("UAV is set to READ_ONLY");
  }
  engine->write(ACI_COMM_CMD::ctrl_enabled, (value ? 1 : 0));
}

void
acc::UAV::_add_write_ctrl() {
  if (_ctrl_mode == CTRL_MODE::READ_ONLY) return;
  std::cout << "ADD WRITE" << std::endl;
  engine->add_write(0, ACI_COMM_CMD::ctrl_mode,
                       ACI_COMM_CMD::ctrl_enabled,
                       ACI_COMM_CMD::disable_motor_onoff_by_stick);
}

void
acc::UAV::_write_ctrl() {
  if (_ctrl_mode == CTRL_MODE::READ_ONLY) return;
  std::cout << "EXC WRITE" << std::endl;
  engine->write(ACI_COMM_CMD::ctrl_mode, 0,
                ACI_COMM_CMD::disable_motor_onoff_by_stick, 1);
}
