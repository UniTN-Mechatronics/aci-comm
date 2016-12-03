#include "bus.hpp"



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
    ::close(_port_state);
}

void 
acc::SerialBus::_setup_port() {
    tcgetattr(_port_state, &_port_settings);
    cfsetispeed(&_port_settings, _baud);    
    cfsetospeed(&_port_settings, _baud);    
    _port_settings.c_cflag = _baud | CS8 | CREAD | CLOCAL;
    _port_settings.c_iflag = IGNPAR;
    _port_settings.c_oflag = 0;
    _port_settings.c_lflag = 0;
    if(tcsetattr(_port_state, TCSANOW, &_port_settings) != 0) {
        throw std::runtime_error("cannot apply settings to port");
    }
}

