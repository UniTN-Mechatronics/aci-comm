#ifndef _ACI_COMM_UAV_FRAME_HPP_
#define _ACI_COMM_UAV_FRAME_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "aci_comm_uav.hpp"
#include "conversion_lambda.hpp"

namespace acc 
{
    template<class T, class FloatingPointPrecision>
    class Angles 
    {
    private:

        Angles(T *uav_ptr) {
            pitch.ChannelRead<T,  FloatingPointPrecision>::_uav_ptr = uav_ptr;
            pitch.ChannelWrite<T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            roll.ChannelRead<T,   FloatingPointPrecision>::_uav_ptr = uav_ptr;
            roll.ChannelWrite<T,  FloatingPointPrecision>::_uav_ptr = uav_ptr;
            yaw.ChannelRead<T,    FloatingPointPrecision>::_uav_ptr = uav_ptr;
        };

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

        template<class TP, class ReturnType>
        class ChannelRead: public Channel<TP>
        {
        public:
            virtual ~ChannelRead() {};
        
            ChannelRead&
            enable_read(int packet) {
                Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);                                  
                Channel<TP>::_uav_ptr->engine->add_read(packet, _read_type);                 
                return *this; 
            }

            ReturnType
            read() {
                Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);                                  
                return _read_conversion(Channel<TP>::_uav_ptr->engine->read(_read_type));
            }

            ACI_COMM_VAR
            get_read_id() { return _read_type; }

        protected:
            virtual ReturnType 
            _read_conversion(int value) {
                return (ReturnType)value;
            }

            ACI_COMM_VAR _read_type;
        };

        
        template<class TP, class ArgType>
        class ChannelWrite: public Channel<TP>
        {
        public:
            virtual ~ChannelWrite() {};

            ChannelWrite&
            enable_write(int packet) {
                Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);                                  
                _ctrl_mode_check();                                             
                Channel<TP>::_uav_ptr->engine->add_write(packet, _write_type);               
                return *this;
            }

            ChannelWrite&
            write(ArgType val) {
                Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);                                  
                auto val_conv = _write_conversion(val);                         
                Channel<TP>::_uav_ptr->engine->write(val_conv, val);                         
                return *this;     
            }

            ACI_COMM_CMD
            get_write_id() { return _write_type; }

        protected:
            ACI_COMM_CMD _write_type;

            virtual int 
            _write_conversion(ArgType value) {
                return (int)value;
            }

            virtual void
            _ctrl_mode_check() {
                return;
                if (Channel<TP>::_uav_ptr->_ctrl_mode == CTRL_MODE::DMC || Channel<TP>::_uav_ptr->_ctrl_mode == CTRL_MODE::CTRL) return;
                throw std::runtime_error("Pitch can be written only with control mode setted to DMC or CTRL");
            }
        };
        
        /*
        *    __          
        *   |__).|_ _|_  
        *   |   ||_(_| ) 
        */
        template<class TP, class ReturnType, class ArgsType>
        class Pitch: public virtual ChannelRead<TP, ReturnType>, public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Angles;

            Pitch() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angle_pitch;
                ChannelWrite<TP, ReturnType>::_write_type = ACI_COMM_CMD::CTRL_pitch;
            };

        protected:
            ReturnType 
            _read_conversion(int value) {
                return angle_read_conv(value);
            }

            int 
            _write_conversion(ReturnType value) {
                return (int)value;
            }
        };


        /*
        *    __      
        *   |__)_ || 
        *   | \(_)|| 
        */
        template<class TP, class ReturnType, class ArgsType>
        class Roll: public virtual ChannelRead<TP, ReturnType>, public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Angles;

            Roll() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angle_roll;
                ChannelWrite<TP, ReturnType>::_write_type = ACI_COMM_CMD::CTRL_roll;
            };

        protected:
            ReturnType 
            _read_conversion(int value) {
                return angle_read_conv(value);
            }

            int 
            _write_conversion(ReturnType value) {
                return (int)value;
            }
        };


        /*
        *   \_/_     
        *    |(_|\)/ 
        */
        template<class TP, class ReturnType>
        class Yaw: public virtual ChannelRead<TP, ReturnType>
        {
        public:
            friend class Angles;

            Yaw() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angle_yaw;
            };

        protected:
            ReturnType 
            _read_conversion(int value) {
                return angle_read_conv(value);
            }
        };

    public:
        friend class UAV;
        Yaw<T, FloatingPointPrecision> yaw;
        Roll<T, FloatingPointPrecision, FloatingPointPrecision> roll;
        Pitch<T, FloatingPointPrecision, FloatingPointPrecision> pitch;
        Angles() {};
    };

};

#endif // __cplusplus
#endif // _ACI_COMM_UAV_FRAME_HPP_

