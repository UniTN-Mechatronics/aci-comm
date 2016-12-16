/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 - Amedeo Setti, Mirko Brentari, Matteo Ragni
 *                      University of Trento (Italy) - Mechatronics Group
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _ACI_COMM_UAV_MOTORS_HPP_
#define _ACI_COMM_UAV_MOTORS_HPP_
#ifdef __cplusplus

#include <initializer_list>
#include <array>
#include "engine.hpp"
#include "aci_comm_uav.hpp"
#include "conversion_lambda.hpp"
#include "uav_commons.hpp"

namespace acc
{
    template<class T, class FloatingPointPrecision>
    class Motor: public virtual ChannelRead<T, int>, public virtual ChannelWrite<T, FloatingPointPrecision>
    {
    private:

        Motor(T *uav_ptr, ACI_COMM_VAR aci_comm_var, ACI_COMM_CMD aci_comm_cmd) {
            ChannelRead<T, int>::_uav_ptr = uav_ptr;
            ChannelWrite<T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            ChannelRead<T, int>::_read_type = aci_comm_var;
            ChannelWrite<T, FloatingPointPrecision>::_write_type = aci_comm_cmd;
        };

    protected:
        int
        _read_conversion(int value) {
            return motor_rpm_read_conv(value);
        }

        int
        _write_conversion(FloatingPointPrecision value) {
            return DIMC_motor_write_conv(value);
        }

        void
        _ctrl_mode_check() {
            if (ChannelWrite<T, FloatingPointPrecision>::_uav_ptr->_ctrl_mode == CTRL_MODE::DIMC) return;
            throw std::runtime_error("Motors can be controlled only with control mode set to DIMC");
        }

    public:
        friend class UAV;
        template<class K, class KK> friend class MotorCollection;
        Motor() {};

        void
        start() {
            DIMC_motor_write_conv(value);
        }

        void
        stop() {
            DIMC_motor_write_conv(value);
        }

    };

    template<class T, class FloatingPointPrecision>
    class MotorCollection {
    private:
        using Motor_ = Motor<T, FLOATING_POINT_PRECISION>;
        int _number_of_motors = -1;
        std::vector<Motor<T, FloatingPointPrecision>> _motors;

        MotorCollection(T *uav_ptr, int number_of_motors) {
            if (number_of_motors == 4) {
                _motors.push_back(Motor_(uav_ptr, ACI_COMM_VAR::motor_rpm_1, ACI_COMM_CMD::DIMC_motor_1));
                _motors.push_back(Motor_(uav_ptr, ACI_COMM_VAR::motor_rpm_2, ACI_COMM_CMD::DIMC_motor_2));
                _motors.push_back(Motor_(uav_ptr, ACI_COMM_VAR::motor_rpm_3, ACI_COMM_CMD::DIMC_motor_3));
                _motors.push_back(Motor_(uav_ptr, ACI_COMM_VAR::motor_rpm_4, ACI_COMM_CMD::DIMC_motor_4));
            } else if (number_of_motors == 6) {
                _motors.push_back(Motor_(uav_ptr, ACI_COMM_VAR::motor_rpm_1, ACI_COMM_CMD::DIMC_motor_1));
                _motors.push_back(Motor_(uav_ptr, ACI_COMM_VAR::motor_rpm_2, ACI_COMM_CMD::DIMC_motor_2));
                _motors.push_back(Motor_(uav_ptr, ACI_COMM_VAR::motor_rpm_3, ACI_COMM_CMD::DIMC_motor_3));
                _motors.push_back(Motor_(uav_ptr, ACI_COMM_VAR::motor_rpm_4, ACI_COMM_CMD::DIMC_motor_4));
                _motors.push_back(Motor_(uav_ptr, ACI_COMM_VAR::motor_rpm_5, ACI_COMM_CMD::DIMC_motor_5));
                _motors.push_back(Motor_(uav_ptr, ACI_COMM_VAR::motor_rpm_6, ACI_COMM_CMD::DIMC_motor_6));
            } else {
                throw std::runtime_error("The number of motors can be only FOUR or SIX");
            }
            _number_of_motors = number_of_motors;
        };

    public:

        friend class UAV;
        MotorCollection() {};

        Motor<T, FloatingPointPrecision>
        operator[](int index) {
            if (index < 0 || index > (_number_of_motors - 1)) {
                std::runtime_error("Motors index is or greater than number of motors or less than zero");
            }
            return _motors[index];
        }

        MotorCollection&
        enable_read(int packet) {
            for (auto &m : _motors) m.enable_read(packet);
            return *this;
        }

        MotorCollection&
        enable_write(int packet) {
            for (auto &m : _motors) m.enable_write(packet);
            return *this;
        }

        MotorCollection&
        write(std::array<FloatingPointPrecision, 4> write_values) {
            if (_number_of_motors != 4) throw std::runtime_error("Write motors, number of motors is not FOUR");
            for (int i = 0; i < 4; ++i) _motors[i].write(write_values[i]);
            return *this;
        }

        MotorCollection&
        write(std::initializer_list<FloatingPointPrecision> write_values) {
            if ((_number_of_motors == -1) || (static_cast<int>(write_values.size()) != _number_of_motors)) {
                throw std::runtime_error("Write motors, number of motors is not FOUR or SIX");
            }
            int i = 0;
            for (auto &wv : write_values) {
                _motors[i].write(wv);
                ++i;
            }
            return *this;
        }

        std::vector<FloatingPointPrecision>
        read() {
            std::vector<FloatingPointPrecision> read_m;
            for (auto &m : _motors) {
                read_m.push_back(m.read());
            }
            return read_m;
        }

    }; // End MotorCollection

}; // end namespace


#endif // __cplusplus
#endif // _ACI_COMM_UAV_MOTORS_HPP_
