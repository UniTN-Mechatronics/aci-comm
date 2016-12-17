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

#include "aci_comm_engine_bus.hpp"


void 
acc::SerialBus::open() {
    #if ACICOMM_TTY_INFO == 1
        std::cout << name << " opening port: " << _port << std::endl;
    #endif

    _port_state = ::open(_port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
    if (_port_state < 0) throw std::runtime_error(name + " port not opened!");
    _setup_port();
    _open = true;

    #if ACICOMM_TTY_INFO == 1
        std::cout << name << " port state: " << _port_state << std::endl;
    #endif
}

void 
acc::SerialBus::close() {
    if (!_open) return;
    usleep(1000);
    ::close(_port_state);
}

void 
acc::SerialBus::_setup_port() {
    if (tcgetattr(_port_state, &_port_settings) != 0) {
        throw std::runtime_error(name + " cannot get params!");
    }
    cfsetispeed(&_port_settings, settings.baud);    
    cfsetospeed(&_port_settings, settings.baud);    
    _port_settings.c_cflag = settings.c_cflag;
    _port_settings.c_iflag = settings.c_iflag;
    _port_settings.c_oflag = settings.c_oflag;
    _port_settings.c_lflag = settings.c_lflag;
    if(tcsetattr(_port_state, TCSANOW, &_port_settings) != 0) {
        throw std::runtime_error("cannot apply settings to port");
    }
}

