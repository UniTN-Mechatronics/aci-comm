#ifndef _ACI_COMM_UAV_HPP_
#define _ACI_COMM_UAV_HPP_
#ifdef __cplusplus

#include <array>

#include "engine.hpp"
#include "uav_commons.hpp"
#include "uav_frame.hpp"
#include "uav_motors.hpp"

#ifndef FLOATING_POINT_PRECISION
#define FLOATING_POINT_PRECISION float
#endif

namespace acc 
{

    class UAV
    {
    public:
        friend class Angles<UAV, FLOATING_POINT_PRECISION>;
        friend class Motor<UAV, FLOATING_POINT_PRECISION>;
        friend class Channel<UAV>;
        friend class ChannelRead<UAV, FLOATING_POINT_PRECISION>;
        friend class ChannelRead<UAV, int>;
        friend class ChannelWrite<UAV, FLOATING_POINT_PRECISION>;

        using Attitude = Angles<UAV, FLOATING_POINT_PRECISION>;
        using Motor = Motor<UAV, FLOATING_POINT_PRECISION>;
        
        /**
        *   SerialBus UAV constructor.
        */
        UAV(std::string port, int baud_rate, CTRL_MODE mode) : _ctrl_mode(mode) {
            engine = &Engine<SerialBus>::init(port, baud_rate);
            attitude = Attitude(this);
            motors[0] = Motor(this, ACI_COMM_VAR::motor_rpm_1, ACI_COMM_CMD::DIMC_motor_1);
            motors[1] = Motor(this, ACI_COMM_VAR::motor_rpm_2, ACI_COMM_CMD::DIMC_motor_2);
            motors[2] = Motor(this, ACI_COMM_VAR::motor_rpm_3, ACI_COMM_CMD::DIMC_motor_3);
            motors[3] = Motor(this, ACI_COMM_VAR::motor_rpm_4, ACI_COMM_CMD::DIMC_motor_4);
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
        std::array<Motor, MOTORS_NUM> motors;

        // Settings
        typedef struct Settings {
            int update_frequency = 1000; 
        } settings; 

        CTRL_MODE 
        ctrl_mode() {
            return _ctrl_mode;
        }

    private:
        Engine<SerialBus>* engine;
        CTRL_MODE _ctrl_mode;

        void _add_write_ctrl();
        void _write_ctrl();
    };

};





#endif // __cplusplus
#endif // _ACI_COMM_UAV_HPP_
