#ifndef _ACI_COMM_UAV_HPP_
#define _ACI_COMM_UAV_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "uav_frame.hpp"

namespace acc 
{
	
	class UAV
	{
	public:
		
		/**
		*	SerialBus UAV constructor.
		*/
		UAV(std::string port, int baud_rate) {
			ae = &Engine<SerialBus>::init(port, baud_rate);
			angles.engine = ae;
			angles.pitch.engine = ae;
			angles.roll.engine = ae;
			angles.yaw.engine = ae;
		};

		// Setup
		void set_port(std::string port_id);

		// Run
		void start(); 
		void stop(); 

		// Packets
		Angles angles;

	private:
		Engine<SerialBus>* ae;
		

	};

};





#endif // __cplusplus
#endif // _ACI_COMM_UAV_HPP_
