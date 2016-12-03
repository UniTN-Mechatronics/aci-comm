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

        SerialBus(std::tuple<std::string, int> args) {
            name = __func__;
            _port = std::get<0>(args);
            _port_state = std::get<1>(args);
        };
        ~SerialBus() { close(); };

        /**
        *   Deleted copy constructor and
        *   copy operator.
        */
        SerialBus(SerialBus const& sb) {
            name = __func__;
            // TODO;
        };
        void operator=(SerialBus const&) = delete;

        void 
        set_baud(int baud) {
            _baud = baud;
        }

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
        int _baud = B57600;
        bool _open = false;

        void _setup_port();
    };

}; // End namespace

#endif // __cplusplus
#endif // _ACI_COMM_BUS_HPP_
