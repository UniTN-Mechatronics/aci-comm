#ifndef _ACI_COMM_UAV_HPP_
#define _ACI_COMM_UAV_HPP_
#ifdef __cplusplus

#include <array>

#include "engine.hpp"
#include "uav_commons.hpp"
#include "uav_frame.hpp"
#include "uav_rc_channels.hpp"
#include "uav_motors.hpp"

namespace acc
{
    enum class UAV_Z {
      UPWARD = -1,
      DOWNWARD = 1
    };

    class UAV
    {
    public:
        friend class Angles<UAV, FLOATING_POINT_PRECISION>;
        friend class Motor<UAV, FLOATING_POINT_PRECISION>;
        friend class RCChannel <UAV, FLOATING_POINT_PRECISION>;

        /* All channels combination */
        friend class Channel<UAV>;
        friend class ChannelRead<UAV, FLOATING_POINT_PRECISION>;
        friend class ChannelRead<UAV, int>;
        friend class ChannelWrite<UAV, FLOATING_POINT_PRECISION>;
        friend class ChannelWrite<UAV, int>;

        using Attitude = Angles<UAV, FLOATING_POINT_PRECISION>;
        using Motors = Motor<UAV, FLOATING_POINT_PRECISION>;

        using RCChannels = RCChannel<UAV, FLOATING_POINT_PRECISION>;

        /**
        *   SerialBus UAV constructor.
        */
        UAV(std::string port, int baud_rate, CTRL_MODE mode) : _ctrl_mode(mode) {
            engine = &Engine<SerialBus>::init(port, baud_rate);
            attitude = Attitude(this);
            motors[0] = Motors(this, ACI_COMM_VAR::motor_rpm_1, ACI_COMM_CMD::DIMC_motor_1);
            motors[1] = Motors(this, ACI_COMM_VAR::motor_rpm_2, ACI_COMM_CMD::DIMC_motor_2);
            motors[2] = Motors(this, ACI_COMM_VAR::motor_rpm_3, ACI_COMM_CMD::DIMC_motor_3);
            motors[3] = Motors(this, ACI_COMM_VAR::motor_rpm_4, ACI_COMM_CMD::DIMC_motor_4);

            rc_ch[0] = RCChannels(this, ACI_COMM_VAR::RC_channel_0);
            rc_ch[1] = RCChannels(this, ACI_COMM_VAR::RC_channel_1);
            rc_ch[2] = RCChannels(this, ACI_COMM_VAR::RC_channel_2);
            rc_ch[3] = RCChannels(this, ACI_COMM_VAR::RC_channel_3);
            rc_ch[4] = RCChannels(this, ACI_COMM_VAR::RC_channel_4);
            rc_ch[5] = RCChannels(this, ACI_COMM_VAR::RC_channel_5);
            rc_ch[6] = RCChannels(this, ACI_COMM_VAR::RC_channel_6);
            rc_ch[7] = RCChannels(this, ACI_COMM_VAR::RC_channel_7);

            _add_write_ctrl();
        };

        ~UAV() {
            engine->stop();
        }

        // Setup
        void set_port(std::string port_id);
        std::string port();

        // Run
        void start();
        void stop();

        // Controller setup
        void control_enable(bool value);

        // Packets
        Attitude attitude;
        std::array<Motors, MOTORS_NUM> motors;
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

        void _add_write_ctrl();
        void _write_ctrl();
    };

};





#endif // __cplusplus
#endif // _ACI_COMM_UAV_HPP_
