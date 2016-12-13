#ifndef _ACI_COMM_UAV_FRAME_HPP_
#define _ACI_COMM_UAV_FRAME_HPP_
#ifdef __cplusplus

#include "engine.hpp"

namespace acc 
{
	
	class Angles 
	{
	private:
		class Pitch 
		{
		public:
			friend class UAV;
			void enable_read(int packet) {
				engine->add_read(packet, ACI_COMM_VAR::angle_pitch);
			}
			void enable_write(int packet) {
				engine->add_write(packet, ACI_COMM_CMD::CTRL_pitch);
			}
			double read() { 
				return engine->read(ACI_COMM_VAR::angle_pitch);
			}
			void write(double val) {
				engine->write(ACI_COMM_CMD::CTRL_pitch, val);
			}
		protected:
			Engine<SerialBus>* engine = NULL;
		};
	
		class Roll 
		{
		public:
			friend class UAV;
			void enable_read(int packet) {
				engine->add_read(packet, ACI_COMM_VAR::angle_roll);
			}
			void enable_write(int packet) {
				engine->add_write(packet, ACI_COMM_CMD::CTRL_roll);
			}
			double read() { 
				return engine->read(ACI_COMM_VAR::angle_roll);
			}
			void write(double val) {
				engine->write(ACI_COMM_CMD::CTRL_roll, val);
			}
		protected:
			Engine<SerialBus>* engine = NULL;
		};
	
		class Yaw 
		{
		public:
			friend class UAV;
			void enable_read(int packet) {
				engine->add_read(packet, ACI_COMM_VAR::angle_yaw);
			}
			double read() { 
				return engine->read(ACI_COMM_VAR::angle_yaw);
			}
		protected:
			Engine<SerialBus>* engine = NULL;
		};

	public:
		friend class UAV;
		Yaw yaw;
		Pitch pitch;
		Roll roll;

	protected:
		Engine<SerialBus>* engine = NULL;
	};

};

#endif // __cplusplus
#endif // _ACI_COMM_UAV_FRAME_HPP_

