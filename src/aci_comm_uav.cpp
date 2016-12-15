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
    frame       = Frame(this);
    motors[0]   = Motors(this, ACI_COMM_VAR::motor_rpm_1, ACI_COMM_CMD::DIMC_motor_1);
    motors[1]   = Motors(this, ACI_COMM_VAR::motor_rpm_2, ACI_COMM_CMD::DIMC_motor_2);
    motors[2]   = Motors(this, ACI_COMM_VAR::motor_rpm_3, ACI_COMM_CMD::DIMC_motor_3);
    motors[3]   = Motors(this, ACI_COMM_VAR::motor_rpm_4, ACI_COMM_CMD::DIMC_motor_4);

    rc_ch[0]    = RCChannels(this, ACI_COMM_VAR::RC_channel_0);
    rc_ch[1]    = RCChannels(this, ACI_COMM_VAR::RC_channel_1);
    rc_ch[2]    = RCChannels(this, ACI_COMM_VAR::RC_channel_2);
    rc_ch[3]    = RCChannels(this, ACI_COMM_VAR::RC_channel_3);
    rc_ch[4]    = RCChannels(this, ACI_COMM_VAR::RC_channel_4);
    rc_ch[5]    = RCChannels(this, ACI_COMM_VAR::RC_channel_5);
    rc_ch[6]    = RCChannels(this, ACI_COMM_VAR::RC_channel_6);
    rc_ch[7]    = RCChannels(this, ACI_COMM_VAR::RC_channel_7);

    magnetometer = MagnetoMeters(this);
    gps = GPS(this);

    _add_write_ctrl();
}

void
acc::UAV::_add_write_ctrl() {
    if (_ctrl_mode == CTRL_MODE::READ_ONLY) return;
    engine->add_write(0, ACI_COMM_CMD::ctrl_mode,
                         ACI_COMM_CMD::ctrl_enabled,
                         ACI_COMM_CMD::disable_motor_onoff_by_stick);
}

/**
*   For safety reason, we disable the motor onoff by stick
*   by default.
*/
void
acc::UAV::_write_ctrl() {
    if (_ctrl_mode == CTRL_MODE::READ_ONLY) return;
    engine->write(ACI_COMM_CMD::ctrl_mode, 0,
                  ACI_COMM_CMD::disable_motor_onoff_by_stick, 0); 
}
