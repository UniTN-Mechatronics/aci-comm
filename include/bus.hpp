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

        void 
        set_port(std::string port) {
            _port = port;
        }

        std::string 
        port() {
            return _port;
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
        bool _open = false;

        void _setup_port();
    };

}; // End namespace

#endif // __cplusplus
#endif // _ACI_COMM_BUS_HPP_
