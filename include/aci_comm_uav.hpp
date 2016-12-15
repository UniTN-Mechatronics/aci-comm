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

#ifndef _ACI_COMM_UAV_HPP_
#define _ACI_COMM_UAV_HPP_
#ifdef __cplusplus

#include <array>

#include "engine.hpp"
#include "uav_commons.hpp"
#include "uav_frame.hpp"
#include "uav_rc_channels.hpp"
#include "uav_motors.hpp"
#include "uav_magnetometer.hpp"
#include "uav_gps.hpp"
#include "uav_info.hpp"
#include "uav_logger.hpp"

namespace acc
{
    class UAV
    {
    public:
        friend class Frames<UAV, FLOATING_POINT_PRECISION>;
        friend class Motor<UAV, FLOATING_POINT_PRECISION>;
        friend class MotorCollection<UAV, FLOATING_POINT_PRECISION>;
        friend class RCChannel<UAV, FLOATING_POINT_PRECISION>;
        friend class RCChannelCollection<UAV, FLOATING_POINT_PRECISION>;
        friend class MagnetoMeter<UAV, FLOATING_POINT_PRECISION>;
        friend class GPSS<UAV, FLOATING_POINT_PRECISION>;
        friend class Infos<UAV, FLOATING_POINT_PRECISION>;

        /* All channel combinations */
        friend class Channel<UAV>;
        friend class ChannelRead<UAV, FLOATING_POINT_PRECISION>;
        friend class ChannelRead<UAV, int>;
        friend class ChannelWrite<UAV, FLOATING_POINT_PRECISION>;
        friend class ChannelWrite<UAV, int>;

        /* Using directives */
        using Frame = Frames<UAV, FLOATING_POINT_PRECISION>;
        using Motors = MotorCollection<UAV, FLOATING_POINT_PRECISION>;
        using MagnetoMeters = MagnetoMeter<UAV, FLOATING_POINT_PRECISION>;
        using GPS = GPSS<UAV, FLOATING_POINT_PRECISION>;
        using RCChannels = RCChannelCollection<UAV, FLOATING_POINT_PRECISION>;
        using Info = Infos<UAV, FLOATING_POINT_PRECISION>;

        /**
        *   SerialBus UAV constructor.
        */
        UAV(std::string port, int baud_rate, CTRL_MODE mode) :
          _ctrl_mode(mode),
          _ctrl_bit(0) {
            engine = &Engine<SerialBus>::init(port, baud_rate);
            _uav_init();
        };

        /**
        *   SerialBus UAV constructor
        *   with Logger
        */
        //template<class LoggerType>
        UAV(std::string port, int baud_rate, CTRL_MODE mode, bool logger_) :
          _ctrl_mode(mode),
          _ctrl_bit(0) {
            engine = &Engine<SerialBus>::init(port, baud_rate);
            _uav_init();
        };

        ~UAV() {
            engine->stop();
        }

        // Setup
        UAV& set_port(std::string port_id);
        std::string port();

        // Run
        UAV& start();
        UAV& stop();

        // Controller setup
        UAV& control_enable(bool value);

        // Packets
        Frame frame;
        Motors motors;
        MagnetoMeters magnetometer;
        GPS gps;
        Info info;
        RCChannels rc_ch;

        // Settings
        typedef struct Settings {
            int update_frequency = 1000;
        } settings;

        CTRL_MODE
        ctrl_mode() {
            return _ctrl_mode;
        }

        // Orientation
        UAV_Z orientation = UAV_Z::DOWNWARD;  // TODO: insert orientation inside requested vars

    private:
        Engine<SerialBus>* engine;
        CTRL_MODE _ctrl_mode;
        unsigned int _ctrl_bit;


        void _uav_init();
        void _add_write_ctrl();
        void _write_ctrl();
    };

};


#endif // __cplusplus
#endif // _ACI_COMM_UAV_HPP_
