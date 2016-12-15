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
    class Frames
    {
    private:

        Frames(T *uav_ptr) {
            pitch.ChannelRead   <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            pitch.ChannelWrite  <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            roll.ChannelRead    <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            roll.ChannelWrite   <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            yaw._update_write_type(uav_ptr);

            pitch_d.ChannelRead <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            pitch_d.ChannelWrite<T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            roll_d.ChannelRead  <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            roll_d.ChannelWrite <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            yaw_d.ChannelRead   <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;

            x_dd.ChannelRead    <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            y_dd.ChannelRead    <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            z_dd.ChannelRead    <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;

            y_dd.YZDotDot       <T, FloatingPointPrecision>::_read_type = ACI_COMM_VAR::acc_y; // TODO Check THIS!! To avoid class duplication.
            z_dd.YZDotDot       <T, FloatingPointPrecision>::_read_type = ACI_COMM_VAR::acc_z; // TODO Check THIS!!

            thrust._update_write_type(uav_ptr);
        };

        //   ___ _ _      _
        //  | _ (_) |_ __| |_
        //  |  _/ |  _/ _| ' \
        //  |_| |_|\__\__|_||_|
        template<class TP, class ReturnType, class ArgsType>
        class Pitch : public virtual ChannelRead<TP, ReturnType>, public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Frames;

            Pitch() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angle_pitch;
                ChannelWrite<TP, ArgsType>::_write_type = ACI_COMM_CMD::CTRL_pitch; // TODO Check map value... DMC_pitch?
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
        class PitchDot : public virtual ChannelRead<TP, ReturnType>, public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Frames;

            PitchDot() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angvel_pitch;
                ChannelWrite<TP, ArgsType>::_write_type = ACI_COMM_CMD::DMC_pitch; // TODO Check map value... CTRL_pitch?
            };

        protected:
            ReturnType
            _read_conversion(int value) {
                return angvel_read_conv(value) *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation); // TODO check if correct;
            }

            int
            _write_conversion(ArgsType value) {
                return DMC_Frames_write_conv(value *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation)); // TODO check if correct
            }

            void
            _ctrl_mode_check() {
                if (ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_mode == CTRL_MODE::DMC) return;
                throw std::runtime_error("Pitch rate can be controlled only in DMC mode");
            }
        };


        //   ___     _ _
        //  | _ \___| | |
        //  |   / _ \ | |
        //  |_|_\___/_|_|
        template<class TP, class ReturnType, class ArgsType>
        class Roll : public virtual ChannelRead<TP, ReturnType>, public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Frames;

            Roll() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angle_roll;
                ChannelWrite<TP, ArgsType>::_write_type = ACI_COMM_CMD::CTRL_roll; // TODO Check map value... DMC_roll?
            };

        protected:
            ReturnType
            _read_conversion(int value) {
                return angle_read_conv(value); // TODO Check if correct
            }

            int
            _write_conversion(ArgsType value) {
                return CTRL_pitch_roll_write_conv(value); // TODO Check if correct
            }
        };

        template<class TP, class ReturnType, class ArgsType>
        class RollDot : public virtual ChannelRead<TP, ReturnType>, public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Frames;

            RollDot() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angvel_roll;
                ChannelWrite<TP, ArgsType>::_write_type = ACI_COMM_CMD::DMC_roll; // TODO Check map value... CTRL_pitch?
            };

        protected:
            ReturnType
            _read_conversion(int value) {
                return angvel_read_conv(value);
            }

            int
            _write_conversion(ReturnType value) {
                return DMC_Frames_write_conv(value); // TODO check if correct
            }

            void
            _ctrl_mode_check() {
                if (ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_mode == CTRL_MODE::DMC) return;
                throw std::runtime_error("Roll rate can be controlled only in DMC mode");
            }
        };

        //  __   __
        //  \ \ / /_ ___ __ __
        //   \ V / _` \ V  V /
        //    |_|\__,_|\_/\_/
        template<class TP, class ReturnType>
        class Yaw : public virtual ChannelRead<TP, ReturnType>
        {
        public:
            friend class Frames;

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

        template<class TP, class ReturnType, class ArgsType>
        class YawDot : public virtual ChannelRead<TP, ReturnType>, public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Frames;

            YawDot() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angvel_yaw;
            };

        protected:
            ReturnType
            _read_conversion(int value) {
                return angvel_read_conv(value) *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation); // TODO check if correct
            }

            YawDot& _update_write_type(TP *uav_ptr) {
                if (uav_ptr->ctr_mode() == CTRL_MODE::CTRL) {
                  ChannelWrite<TP, ArgsType>::_write_type = ACI_COMM_CMD::CTRL_yaw;
                } else {
                  ChannelWrite<TP, ArgsType>::_write_type = ACI_COMM_CMD::DMC_yaw;
                }
                ChannelWrite <T, ArgsType>::_uav_ptr = uav_ptr;
                ChannelRead <T, ReturnType>::_uav_ptr = uav_ptr;
            }

            void
            _ctrl_mode_check() {
                if (ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_mode == CTRL_MODE::DMC ||
                    ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_mode == CTRL_MODE::CTRL) return;
                throw std::runtime_error("Roll rate can be controlled only in DMC mode");
            }

            int
            _write_conversion(ArgsType value) {
                if (ChannelWrite<TP, ArgsType>::_write_type == ACI_COMM_CMD::CTRL_thrust) {
                  return CTRL_thrust_write_conv(value);
                } else {
                  return DMC_thrust_write_conv(value);
                }
            }
        };

        //     _             _              _   _
        //    /_\  __ __ ___| |___ _ _ __ _| |_(_)___ _ _  ___
        //   / _ \/ _/ _/ -_) / -_) '_/ _` |  _| / _ \ ' \(_-<
        //  /_/ \_\__\__\___|_\___|_| \__,_|\__|_\___/_||_/__/
        template<class TP, class ReturnType>
        class XDotDot : public virtual ChannelRead<TP, ReturnType>
        {
        public:
            friend class Frames;

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
        class YZDotDot : public virtual ChannelRead<TP, ReturnType>
        {
        public:
            friend class Frames;

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

        //   _____ _                _
        //  |_   _| |_  _ _ _  _ __| |_
        //    | | | ' \| '_| || (_-<  _|
        //    |_| |_||_|_|  \_,_/__/\__|
        template<class TP, class ArgType>
        class Thrust : public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Frames;

            Thrust () {};

        protected:
            Thrust& _update_write_type(TP *uav_ptr) {
                if (uav_ptr->ctr_mode() == CTRL_MODE::CTRL) {
                  ChannelWrite<TP, ArgsType>::_write_type = ACI_COMM_CMD::CTRL_thrust;
                } else {
                  ChannelWrite<TP, ArgsType>::_write_type = ACI_COMM_CMD::DMC_thrust;
                }
                ChannelWrite <T, ArgsType>::_uav_ptr = uav_ptr;
            }

            void
            _ctrl_mode_check() {
                if (ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_mode == CTRL_MODE::DMC ||
                    ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_mode == CTRL_MODE::CTRL) return;
                throw std::runtime_error("Roll rate can be controlled only in DMC mode");
            }

            int
            _write_conversion(ReturnType value) {
                if (ChannelWrite<TP, ArgsType>::_write_type == ACI_COMM_CMD::CTRL_thrust) {
                  return CTRL_thrust_write_conv(value);
                } else {
                  return DMC_thrust_write_conv(value);
                }
            }
        };

    public:
        friend class UAV;
        Yaw<T, FloatingPointPrecision> yaw;
        Roll<T, FloatingPointPrecision, FloatingPointPrecision> roll;
        Pitch<T, FloatingPointPrecision, FloatingPointPrecision> pitch;

        YawDot<T, FloatingPointPrecision, FloatingPointPrecision> yaw_d;
        RollDot<T, FloatingPointPrecision, FloatingPointPrecision> roll_d;
        PitchDot<T, FloatingPointPrecision, FloatingPointPrecision> pitch_d;

        XDotDot<T, FloatingPointPrecision> x_dd;
        YZDotDot<T, FloatingPointPrecision> y_dd;
        YZDotDot<T, FloatingPointPrecision> z_dd;

        Thrust<T, FloatingPointPrecision> thrust;

        Frames() {};
    };

};

#endif // __cplusplus
#endif // _ACI_COMM_UAV_FRAME_HPP_
