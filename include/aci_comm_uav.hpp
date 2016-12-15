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

namespace acc
{
    enum class UAV_Z : signed int {
      UPWARD = -1,
      DOWNWARD = 1
    };

    class UAV
    {
    public:
        friend class Angles<UAV, FLOATING_POINT_PRECISION>;
        friend class Motor<UAV, FLOATING_POINT_PRECISION>;
        friend class RCChannel<UAV, FLOATING_POINT_PRECISION>;
        friend class MagnetoMeter<UAV, FLOATING_POINT_PRECISION>;
        friend class GPSS<UAV, FLOATING_POINT_PRECISION>;
        friend class Infos<UAV, FLOATING_POINT_PRECISION>;

        /* All channel combinations */
        friend class Channel<UAV>;
        friend class ChannelRead<UAV, FLOATING_POINT_PRECISION>;
        friend class ChannelRead<UAV, int>;
        friend class ChannelWrite<UAV, FLOATING_POINT_PRECISION>;
        friend class ChannelWrite<UAV, int>;

        using Attitude = Angles<UAV, FLOATING_POINT_PRECISION>;
        using Motors = Motor<UAV, FLOATING_POINT_PRECISION>;

        using MagnetoMeters = MagnetoMeter<UAV, FLOATING_POINT_PRECISION>;
        using GPS = GPSS<UAV, FLOATING_POINT_PRECISION>;
        using RCChannels = RCChannel<UAV, FLOATING_POINT_PRECISION>;
        using Info = Infos<UAV, FLOATING_POINT_PRECISION>;

        /**
        *   SerialBus UAV constructor.
        */
        UAV(std::string port, int baud_rate, CTRL_MODE mode) : _ctrl_mode(mode) {
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
        Attitude attitude;
        std::array<Motors, MOTORS_NUM> motors;
        MagnetoMeters magnetometer;
        GPS gps;
        Info info;
        std::array<RCChannels, RC_CHANNELS_NUM> rc_ch;

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

        void _uav_init();
        void _add_write_ctrl();
        void _write_ctrl();
    };

};


#endif // __cplusplus
#endif // _ACI_COMM_UAV_HPP_
