#ifndef _ACI_COMM_UAV_FRAME_HPP_
#define _ACI_COMM_UAV_FRAME_HPP_
#ifdef __cplusplus

#include <cmath>
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
            yaw.ChannelRead    <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;

            pitch_d.ChannelRead <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            pitch_d.ChannelWrite<T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            roll_d.ChannelRead  <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            roll_d.ChannelWrite <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            yaw_d._update_write_type(uav_ptr);


            x_dd.ChannelRead    <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            y_dd.ChannelRead    <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            z_dd.ChannelRead    <T, FloatingPointPrecision>::_uav_ptr = uav_ptr;

            y_dd.YZDotDot       <T, FloatingPointPrecision>::_read_type = ACI_COMM_VAR::acc_y; // TODO Check THIS!! To avoid class duplication.
            z_dd.YZDotDot       <T, FloatingPointPrecision>::_read_type = ACI_COMM_VAR::acc_z; // TODO Check THIS!!

            thrust._update_write_type(uav_ptr);
        };

        /*   ___ _ _      _
         *  | _ (_) |_ __| |_
         *  |  _/ |  _/ _| ' \
         *  |_| |_|\__\__|_||_|
         */
        template<class TP, class ReturnType, class ArgsType>
        class Pitch : public virtual ChannelRead<TP, ReturnType>, public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Frames;

            Pitch() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angle_pitch;
                ChannelWrite<TP, ArgsType>::_write_type = ACI_COMM_CMD::CTRL_pitch; // TODO Check map value... DMC_pitch?
            };

            ReturnType
            read_rad() {
              return deg2rad(ChannelRead<TP, ReturnType>::read());
            }

            Pitch&
            write_rad(ArgsType val) {
              ChannelWrite<TP, ArgsType>::write(rad2deg(val));
              return this;
            }

            Pitch&
            enable_write(int packet) {
                ChannelWrite<TP, ArgsType>::_check_null_uav_ptr(ChannelWrite<TP, ArgsType>::_uav_ptr);
                ChannelWrite<TP, ArgsType>::_ctrl_mode_check();
                ChannelWrite<TP, ArgsType>::_uav_ptr->engine->add_write(packet, ChannelWrite<TP, ArgsType>::_write_type);
                ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_bit |= static_cast<unsigned int>(CTRL_BIT::Pitch);
                return *this;
            }

        protected:
            ReturnType
            _read_conversion(int value) {
                return angle_read_conv(value) *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation);
            }

            int
            _write_conversion(ReturnType value) {
                return CTRL_pitch_roll_write_conv(value *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation));
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

            ReturnType
            read_rad() {
              return deg2rad(ChannelRead<TP, ReturnType>::read());
            }

            PitchDot&
            write_rad(ArgsType val) {
              ChannelWrite<TP, ArgsType>::write(rad2deg(val));
              return this;
            }

        protected:
            ReturnType
            _read_conversion(int value) {
                return angvel_read_conv(value) *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation); // TODO check if correct;
            }

            int
            _write_conversion(ArgsType value) {
                return DMC_angles_write_conv(value *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation)); // TODO check if correct
            }

            void
            _ctrl_mode_check() {
                if (ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_mode == CTRL_MODE::DMC) return;
                throw std::runtime_error("Pitch rate can be controlled only in DMC mode");
            }
        };


        /*   ___     _ _
         *  | _ \___| | |
         *  |   / _ \ | |
         *  |_|_\___/_|_|
         */
        template<class TP, class ReturnType, class ArgsType>
        class Roll : public virtual ChannelRead<TP, ReturnType>, public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Frames;

            Roll() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angle_roll;
                ChannelWrite<TP, ArgsType>::_write_type = ACI_COMM_CMD::CTRL_roll; // TODO Check map value... DMC_roll?
            };

            ReturnType
            read_rad() {
              return deg2rad(ChannelRead<TP, ReturnType>::read());
            }

            Roll&
            write_rad(ArgsType val) {
              ChannelWrite<TP, ArgsType>::write(rad2deg(val));
              return this;
            }

            Roll&
            enable_write(int packet) {
                ChannelWrite<TP, ArgsType>::_check_null_uav_ptr(ChannelWrite<TP, ArgsType>::_uav_ptr);
                ChannelWrite<TP, ArgsType>::_ctrl_mode_check();
                ChannelWrite<TP, ArgsType>::_uav_ptr->engine->add_write(packet, ChannelWrite<TP, ArgsType>::_write_type);
                ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_bit |= static_cast<unsigned int>(CTRL_BIT::Roll);
                return *this;
            }

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

            ReturnType
            read_rad() {
              return deg2rad(ChannelRead<TP, ReturnType>::read());
            }

            RollDot&
            write_rad(ArgsType val) {
              ChannelWrite<TP, ArgsType>::write(rad2deg(val));
              return this;
            }

        protected:
            ReturnType
            _read_conversion(int value) {
                return angvel_read_conv(value);
            }

            int
            _write_conversion(ReturnType value) {
                return DMC_angles_write_conv(value); // TODO check if correct
            }

            void
            _ctrl_mode_check() {
                if (ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_mode == CTRL_MODE::DMC) return;
                throw std::runtime_error("Roll rate can be controlled only in DMC mode");
            }
        };

        /*  __   __
         *  \ \ / /_ ___ __ __
         *   \ V / _` \ V  V /
         *    |_|\__,_|\_/\_/
         */
        template<class TP, class ReturnType>
        class Yaw : public virtual ChannelRead<TP, ReturnType>
        {
        public:
            friend class Frames;

            Yaw() {
                ChannelRead<TP, ReturnType>::_read_type = ACI_COMM_VAR::angle_yaw;
            };

            ReturnType
            read_rad() {
              return deg2rad(ChannelRead<TP, ReturnType>::read());
            }

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

            ReturnType
            read_rad() {
              return deg2rad(ChannelRead<TP, ReturnType>::read());
            }

            YawDot&
            write_rad(ArgsType val) {
              ChannelWrite<TP, ArgsType>::write(rad2deg(val));
              return this;
            }

            YawDot&
            enable_write(int packet) {
                ChannelWrite<TP, ArgsType>::_check_null_uav_ptr(ChannelWrite<TP, ArgsType>::_uav_ptr);
                _ctrl_mode_check();
                ChannelWrite<TP, ArgsType>::_uav_ptr->engine->add_write(packet, ChannelWrite<TP, ArgsType>::_write_type);
                if (ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_mode == CTRL_MODE::CTRL) {
                  ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_bit |= static_cast<unsigned int>(CTRL_BIT::YawDot);
                }
                return *this;
            }

        protected:
            ReturnType
            _read_conversion(int value) {
                return angvel_read_conv(value) *
                  static_cast<ReturnType>(ChannelRead<TP, ReturnType>::_uav_ptr->orientation); // TODO check if correct
            }

            void
            _update_write_type(TP *uav_ptr) {
                if (uav_ptr->ctrl_mode() == CTRL_MODE::CTRL) {
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

        /*     _             _              _   _
         *    /_\  __ __ ___| |___ _ _ __ _| |_(_)___ _ _  ___
         *   / _ \/ _/ _/ -_) / -_) '_/ _` |  _| / _ \ ' \(_-<
         *  /_/ \_\__\__\___|_\___|_| \__,_|\__|_\___/_||_/__/
         */
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

        /*   _____ _                _
         *  |_   _| |_  _ _ _  _ __| |_
         *    | | | ' \| '_| || (_-<  _|
         *    |_| |_||_|_|  \_,_/__/\__|
         */
        template<class TP, class ArgsType>
        class Thrust : public virtual ChannelWrite<TP, ArgsType>
        {
        public:
            friend class Frames;

            Thrust () {};

            Thrust&
            enable_write(int packet) {
                ChannelWrite<TP, ArgsType>::_check_null_uav_ptr(ChannelWrite<TP, ArgsType>::_uav_ptr);
                _ctrl_mode_check();
                ChannelWrite<TP, ArgsType>::_uav_ptr->engine->add_write(packet, ChannelWrite<TP, ArgsType>::_write_type);
                if (ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_mode == CTRL_MODE::CTRL) {
                  ChannelWrite<TP, ArgsType>::_uav_ptr->_ctrl_bit |= static_cast<unsigned int>(CTRL_BIT::Thrust);
                }
                return *this;
            }

        protected:
            void
            _update_write_type(TP *uav_ptr) {
                if (uav_ptr->ctrl_mode() == CTRL_MODE::CTRL) {
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
            _write_conversion(ArgsType value) {
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

        Frames&
        enable_read_angles(int packet) {
            roll.enable_read(packet);
            pitch.enable_read(packet);
            yaw.enable_read(packet);
            return *this;
        }

        std::array<FloatingPointPrecision, 3>
        read_angles() { // returns rpy
            std::array<FloatingPointPrecision, 3> rpy;
            rpy[0] = roll.read();
            rpy[1] = pitch.read();
            rpy[2] = yaw.read();
            return rpy;
        }

        Frames&
        enable_write_angles(int packet) {
            roll.enable_write(packet);
            pitch.enable_write(packet);
            return *this;
        }

        Frames&
        write_angles(std::array<FloatingPointPrecision, 3> v) {
            roll.write(v[0]);
            pitch.write(v[1]);
            return *this;
        }

        Frames&
        enable_read_angles_d(int packet) {
            roll_d.enable_read(packet);
            pitch_d.enable_read(packet);
            yaw_d.enable_read(packet);
            return *this;
        }

        std::array<FloatingPointPrecision, 3>
        read_angles_d() {
            std::array<FloatingPointPrecision, 3> rpy_d;
            rpy_d[0] = roll_d.read();
            rpy_d[1] = pitch_d.read();
            rpy_d[2] = yaw_d.read();
            return rpy_d;
        }

        Frames&
        enable_read_acc(int packet) {
            x_dd.enable_read(packet);
            y_dd.enable_read(packet);
            z_dd.enable_read(packet);
            return *this;
        }

        std::array<FloatingPointPrecision, 3>
        read_acc() {
            std::array<FloatingPointPrecision, 3> acc;
            acc[0] = x_dd.read();
            acc[1] = y_dd.read();
            acc[2] = z_dd.read();
            return acc;
        }

        std::array<FloatingPointPrecision, 4>
        quaternion() {
            return rpy2quaternion(read_angles());
        }

    };

};

#endif // __cplusplus
#endif // _ACI_COMM_UAV_FRAME_HPP_
