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

#ifndef _ACI_COMM_UAV_COMMONS_HPP_
#define _ACI_COMM_UAV_COMMONS_HPP_
#ifdef __cplusplus

#include "aci_comm_uav.hpp"
#include "aci_comm_misc_conversion_lambda.hpp"

/** 
*   Drone's number of motors.
*   Can be only FOUR or SIX.
*   Default: 4
*/
#ifndef MOTORS_NUM
#define MOTORS_NUM 4
#endif
#if (MOTORS_NUM != 4 && MOTORS_NUM != 6)
#error ERROR_MOTOR_NUMBER 
#endif

#ifndef RC_CHANNELS_NUM
#define RC_CHANNELS_NUM 8
#endif

#ifndef FLOATING_POINT_PRECISION
#define FLOATING_POINT_PRECISION double
#endif

namespace acc
{
    /**
    *   Base class for all the 
    *   write and read properties.
    *   Contains a pointer to the UAV
    *   instance.
    *   Both ChannelRead and ChannelWrite
    *   inherit from this.
    */
    template<class TP>
    class Channel
    {
    public:
        virtual ~Channel() {};

    protected:
        TP *_uav_ptr = NULL;
        void
        _check_null_uav_ptr(TP *uav_ptr) noexcept(false) {
            if (!uav_ptr) throw std::runtime_error("UAV pointer is null!");
        }
    };

    /**
    *   Base read class. 
    *   Inherit from Channel.
    *   Contains methods for enable a
    *   read property, and for read
    *   this property.
    */
    template<class TP, class ReturnType>
    class ChannelRead: public Channel<TP>
    {
    public:
        virtual ~ChannelRead() {};

        virtual ChannelRead&
        enable_read(int packet) {
            Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);
            Channel<TP>::_uav_ptr->engine->add_read(packet, _read_type);
            return *this;
        }

        virtual ReturnType
        read() {
            Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);
            return _read_conversion(Channel<TP>::_uav_ptr->engine->read(_read_type));
        }

        Var
        get_read_id() {
            return _read_type;
        }

    protected:
        virtual ReturnType
        _read_conversion(int value) {
            return (ReturnType)value;
        }

        Var _read_type;
    };

    /**
    *   Base write class. 
    *   Inherit from Channel.
    *   Contains methods for enable a
    *   write property, and for write
    *   this property.
    */
    template<class TP, class ArgType>
    class ChannelWrite: public Channel<TP>
    {
    public:
        virtual ~ChannelWrite() {};

        virtual ChannelWrite&
        enable_write(int packet) {
            Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);
            _ctrl_mode_check();
            Channel<TP>::_uav_ptr->engine->add_write(packet, _write_type);
            return *this;
        }

        virtual ChannelWrite&
        write(ArgType val) {
            Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);
            auto val_conv = _write_conversion(val);
            Channel<TP>::_uav_ptr->engine->write(_write_type, val_conv);
            return *this;
        }

        Cmd
        get_write_id() {
            return _write_type;
        }

    protected:
        Cmd _write_type;

        virtual int
        _write_conversion(ArgType value) {
            return (int)value;
        }

        virtual void
        _ctrl_mode_check() {
            if (Channel<TP>::_uav_ptr->_ctrl_mode == CTRL_MODE::DMC || Channel<TP>::_uav_ptr->_ctrl_mode == CTRL_MODE::CTRL) return;
            throw std::runtime_error("Pitch can be written only with control mode setted to DMC or CTRL");
        }
    };

};

#endif // __cplusplus
#endif // _ACI_COMM_UAV_COMMONS_HPP_
