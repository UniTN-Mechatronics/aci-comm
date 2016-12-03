#ifndef _ACI_COMM_BUS_HPP_
#define _ACI_COMM_BUS_HPP_
#ifdef __cplusplus

#include <termios.h>
#include <unistd.h> 
#include <fcntl.h>  
 #include <string>

#define ACICOMM_TTY_INFO 1
#if ACICOMM_TTY_INFO == 1
    #include <iostream>
#endif

namespace acc 
{

    /**
    *   Here in order to define
    *   Bus friend class.
    */ 
    class Engine;


    /**
    *   Pure abstract class.
    */ 
    class Bus
    {
    public:
        friend class Engine;

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
        SerialBus(std::string port) : _port(port) {
            name = __func__;
            _port_state = -1;
        };
        ~SerialBus() { close(); };

        /**
        *   Deleted copy constructor and
        *   copy operator.
        */
        SerialBus(SerialBus const&) = delete;
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
