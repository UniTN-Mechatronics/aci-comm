#ifndef _ACI_COMM_BUS_HPP_
#define _ACI_COMM_BUS_HPP_
#ifdef __cplusplus

#include <tuple>
#include <termios.h>
#include <unistd.h> 
#include <fcntl.h>  
#include <string>

#define ACICOMM_TTY_INFO 1
#if ACICOMM_TTY_INFO == 1
    #include <iostream>
#endif

#ifndef _ACI_COMM_COMMONS_HPP_
    #include "commons.hpp"
#endif

namespace acc 
{

    /**
    *   Here in order to define
    *   Bus friend class.
    */ 
    template<class BUS>
    class Engine;

    /**
    *   Pure abstract class.
    */ 
    class Bus
    {
    public:
        Bus() {};
        virtual ~Bus() {};

    protected:
        std::string name;
        int _port_state;
        virtual void open() = 0;
        virtual void close() = 0;
    };


    /**
    *   Serial bus class.
    *   You should not inherit from
    *   this.
    */ 
    class SerialBus: public Bus
    {
    public:
        template<class BUS> friend class Engine;
        typedef std::tuple<std::string, int> Args;

        /**
        *   Constructor. 
        */
        SerialBus(Args args) {
            name = __func__;
            _port = std::get<0>(args);
            settings.baud = std::get<1>(args);
            _port_state = -1;
        };
        /**
        *   Copy Constructor.
        */
        SerialBus(const SerialBus& SB) {
            name = SB.name;
            _port = SB._port;
            _port_state = SB._port_state;
            _open = SB._open;
            _port_settings = SB._port_settings;
            settings = SB.settings;
        }
        /**
        *   Deleted copy operator.
        */
        void operator=(SerialBus const&) = delete;
        /**
        *   Destructor, close the port if
        *   open.
        */
        ~SerialBus() { close(); };

        struct PortSettings
        {
            int baud    = B57600;
            int c_cflag = baud | CS8 | CREAD | CLOCAL;
            int c_iflag = IGNPAR;
            int c_oflag = 0;
            int c_lflag = 0;
        } settings;

    protected:
        /**
        *   They will be called from
        *   from the Engine class.
        */
        virtual void open() final;
        virtual void close() final;

    private:
        std::string _port;
        termios _port_settings;
        bool _open = false;

        void _setup_port();
    };

}; // End namespace

#endif // __cplusplus
#endif // _ACI_COMM_BUS_HPP_
