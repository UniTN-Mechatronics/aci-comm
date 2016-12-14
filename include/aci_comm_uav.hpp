#ifndef _ACI_COMM_UAV_HPP_
#define _ACI_COMM_UAV_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "uav_commons.hpp"
#include "uav_frame.hpp"

#ifndef FLOATING_POINT_PRECISION
#define FLOATING_POINT_PRECISION float
#endif

namespace acc 
{

    class UAV
    {
    public:
        friend class Angles<UAV, FLOATING_POINT_PRECISION>;
        friend class Channel<UAV>;
        friend class ChannelRead<UAV, FLOATING_POINT_PRECISION>;
        friend class ChannelWrite<UAV, FLOATING_POINT_PRECISION>;

        using Attitude = Angles<UAV, FLOATING_POINT_PRECISION>;
        
        /**
        *   SerialBus UAV constructor.
        */
        UAV(std::string port, int baud_rate, CTRL_MODE mode) : _ctrl_mode(mode) {
            engine = &Engine<SerialBus>::init(port, baud_rate);
            attitude = Attitude(this);
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

        // Packets
        Attitude attitude;

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
    };

};





#endif // __cplusplus
#endif // _ACI_COMM_UAV_HPP_
