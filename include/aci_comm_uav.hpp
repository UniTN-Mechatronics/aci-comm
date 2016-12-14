#ifndef _ACI_COMM_UAV_HPP_
#define _ACI_COMM_UAV_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "uav_commons.hpp"
#include "uav_frame.hpp"

namespace acc 
{

    class UAV
    {
    public:
        friend class Angles<UAV>;
        
        /**
        *   SerialBus UAV constructor.
        */
        UAV(std::string port, int baud_rate, CTRL_MODE mode) : _ctrl_mode(mode) {
            engine = &Engine<SerialBus>::init(port, baud_rate);
            angles = Angles<UAV>(this);
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
        Angles<UAV> angles;

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
