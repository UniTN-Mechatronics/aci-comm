#include "aci_comm_uav.hpp"


acc::UAV&
acc::UAV::set_port(std::string port_id) {
	engine->bus()->set_port(port_id);
	return *this;
}

std::string
acc::UAV::port() {
	return engine->bus()->port();
}

acc::UAV&
acc::UAV::start() {
	engine->start();
 	_write_ctrl();
 	return *this;
}

acc::UAV&
acc::UAV::stop() {
	engine->stop();
	return *this;
}

acc::UAV&
acc::UAV::control_enable(bool value) {
    if (_ctrl_mode == CTRL_MODE::READ_ONLY) {
      throw std::runtime_error("UAV is set to READ_ONLY");
    }
    engine->write(ACI_COMM_CMD::ctrl_enabled, (value ? 1 : 0));
    return *this;
}

/*
*    ____       _            _
*   |  _ \ _ __(_)_   ____ _| |_ ___
*   | |_) | '__| \ \ / / _` | __/ _ \
*   |  __/| |  | |\ V / (_| | ||  __/
*   |_|   |_|  |_| \_/ \__,_|\__\___|
*
*/
void
acc::UAV::_uav_init() {
    frame  = Frame(this);
    motors = Motors(this, MOTORS_NUM);
    rc_ch  = RCChannels(this);
    magnetometer = MagnetoMeters(this);
    gps = GPS(this);
    _add_write_ctrl();
}

void
acc::UAV::_add_write_ctrl() {
    if (_ctrl_mode == CTRL_MODE::READ_ONLY) return;
    engine->add_write(0, Cmd::ctrl_mode,
                         Cmd::ctrl_enabled,
                         Cmd::disable_motor_onoff_by_stick);
    if (_ctrl_mode == CTRL_MODE::CTRL) engine->add_write(0, Cmd::CTRL_ctrl);
}

/**
*   For safety reason, we disable the motor onoff by stick
*   by default.
*/
void
acc::UAV::_write_ctrl() {
    if (_ctrl_mode == CTRL_MODE::READ_ONLY) return;
    engine->write(Cmd::ctrl_mode, static_cast<int>(_ctrl_mode),
                  Cmd::disable_motor_onoff_by_stick, 0);

    if (_ctrl_mode == CTRL_MODE::CTRL) engine->write(Cmd::CTRL_ctrl, _ctrl_bit);
}
