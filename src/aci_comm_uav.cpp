/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 - Amedeo Setti, Mirko Brentari, Matteo Ragni
 *                      University of Trento (Italy) - Mechatronics Group
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
acc::UAV::start(int e_freq, 
                int e_heartbeat,
                int th_sleep_us, 
                int read_update) {
	engine->start(e_freq, e_heartbeat, th_sleep_us, read_update);
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
    info   = Info(this);    
    gps    = GPS(this);
    magnetometer = MagnetoMeters(this);
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
