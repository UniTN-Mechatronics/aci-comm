#ifndef _ACI_COMM_UAV_FRAME_HPP_
#define _ACI_COMM_UAV_FRAME_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "aci_comm_uav.hpp"
#include "conversion_lambda.hpp"
#include "uav_commons.hpp"

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

