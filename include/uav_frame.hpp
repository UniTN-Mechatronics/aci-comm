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

            d_pitch.ChannelRead<T,  FloatingPointPrecision>::_uav_ptr = uav_ptr;
            d_pitch.ChannelWrite<T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            d_roll.ChannelRead<T,   FloatingPointPrecision>::_uav_ptr = uav_ptr;
            d_roll.ChannelWrite<T,  FloatingPointPrecision>::_uav_ptr = uav_ptr;
            d_yaw.ChannelRead<T,    FloatingPointPrecision>::_uav_ptr = uav_ptr;

            dd_x.ChannelRead<T,    FloatingPointPrecision>::_uav_ptr = uav_ptr;
            dd_y.ChannelRead<T,    FloatingPointPrecision>::_uav_ptr = uav_ptr;
            dd_z.ChannelRead<T,    FloatingPointPrecision>::_uav_ptr = uav_ptr;

            dd_y.YZDotDot<T, FloatingPointPrecision>::_read_type = ACI_COMM_VAR::acc_y; // TODO Check THIS!! To avoid class duplication.
            dd_z.YZDotDot<T, FloatingPointPrecision>::_read_type = ACI_COMM_VAR::acc_z; // TODO Check THIS!!

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
                ChannelWrite<TP, ReturnType>::_write_type = ACI_COMM_CMD::CTRL_pitch; // TODO Check map value... DMC_pitch?
            };

        protected:
            ReturnType
            _read_conversion(int value) {
                return angle_read_conv(value);
            }

            int
            _write_conversion(ReturnType value) {
                return CTRL_pitch_roll_write_conv(value);
            }
        };

        template<class TP, class ReturnType, class ArgsType>
        class PitchDot: public virtual ChannelRead<TP, ReturnType>, public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Angles;

            PitchDot() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angvel_pitch;
                ChannelWrite<TP, ReturnType>::_write_type = ACI_COMM_CMD::DMC_pitch; // TODO Check map value... CTRL_pitch?
            };

        protected:
            ReturnType
            _read_conversion(int value) {
                return angvel_read_conv(value);
            }

            int
            _write_conversion(ReturnType value) {
                return DMC_angles_write_conv(value);
            }

            void
            _ctrl_mode_check() {
                if (ChannelWrite<TP, FloatingPointPrecision>::_uav_ptr->_ctrl_mode == CTRL_MODE::DMC) return;
                throw std::runtime_error("Pitch rate can be controlled only in DMC mode");
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
                ChannelWrite<TP, ReturnType>::_write_type = ACI_COMM_CMD::CTRL_roll; // TODO Check map value... DMC_roll?
            };

        protected:
            ReturnType
            _read_conversion(int value) {
                return angle_read_conv(value) *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation); // TODO Check if correct
            }

            int
            _write_conversion(ReturnType value) {
                return CTRL_pitch_roll_write_conv(value *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation)); // TODO Check if correct
            }
        };

        template<class TP, class ReturnType, class ArgsType>
        class RollDot: public virtual ChannelRead<TP, ReturnType>, public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Angles;

            RollDot() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angvel_roll;
                ChannelWrite<TP, ReturnType>::_write_type = ACI_COMM_CMD::DMC_roll; // TODO Check map value... CTRL_pitch?
            };

        protected:
            ReturnType
            _read_conversion(int value) {
                return angvel_read_conv(value) *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation); // TODO check if correct
            }

            int
            _write_conversion(ReturnType value) {
                return DMC_angles_write_conv(value *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation)); // TODO check if correct
            }

            void
            _ctrl_mode_check() {
                if (ChannelWrite<TP, FloatingPointPrecision>::_uav_ptr->_ctrl_mode == CTRL_MODE::DMC) return;
                throw std::runtime_error("Roll rate can be controlled only in DMC mode");
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
                return angle_read_conv(value) *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation); // TODO check if correct
            }
        };

        template<class TP, class ReturnType>
        class YawDot: public virtual ChannelRead<TP, ReturnType> // TODO And write?? DMC, CTRL?? not written for now
        {
        public:
            friend class Angles;

            YawDot() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angvel_yaw;
            };

        protected:
            ReturnType
            _read_conversion(int value) {
                return angvel_read_conv(value) *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation); // TODO check if correct
            }
        };

        //     _             _              _   _
        //    /_\  __ __ ___| |___ _ _ __ _| |_(_)___ _ _  ___
        //   / _ \/ _/ _/ -_) / -_) '_/ _` |  _| / _ \ ' \(_-<
        //  /_/ \_\__\__\___|_\___|_| \__,_|\__|_\___/_||_/__/

        template<class TP, class ReturnType>
        class XDotDot: public virtual ChannelRead<TP, ReturnType>
        {
        public:
            friend class Angles;

            XDotDot() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::acc_x;
            };

        protected:
            ReturnType
            _read_conversion(int value) {
                return acc_read_conv(value);
            }
        };

        template<class TP, class ReturnType>
        class YZDotDot: public virtual ChannelRead<TP, ReturnType>
        {
        public:
            friend class Angles;

            YZDotDot() {
                // ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::acc_y;
            };

        protected:
            ReturnType
            _read_conversion(int value) {
                return acc_read_conv(value) *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation); // TODO check if correct
            }
        };

    public:
        friend class UAV;
        Yaw<T, FloatingPointPrecision> yaw;
        Roll<T, FloatingPointPrecision, FloatingPointPrecision> roll;
        Pitch<T, FloatingPointPrecision, FloatingPointPrecision> pitch;

        YawDot<T, FloatingPointPrecision> d_yaw;
        RollDot<T, FloatingPointPrecision, FloatingPointPrecision> d_roll;
        PitchDot<T, FloatingPointPrecision, FloatingPointPrecision> d_pitch;

        XDotDot<T, FloatingPointPrecision> dd_x;
        YZDotDot<T, FloatingPointPrecision> dd_y;
        YZDotDot<T, FloatingPointPrecision> dd_z;

        Angles() {};
    };

};

#endif // __cplusplus
#endif // _ACI_COMM_UAV_FRAME_HPP_
