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

#ifndef _ACI_COMM_CONVERSION_LAMBDA_HPP_
#define _ACI_COMM_CONVERSION_LAMBDA_HPP_
#ifdef __cplusplus
#include <cmath>
#include <array>

#ifndef FLOATING_POINT_PRECISION
#define FLOATING_POINT_PRECISION double
#endif

#ifndef MOTOR_MIN_ROTATION_SPEED
#define MOTOR_MIN_ROTATION_SPEED 1075
#endif

#ifndef MOTOR_MAX_ROTATION_SPEED
#define MOTOR_MAX_ROTATION_SPEED 8600
#endif

#define PI 3.14159265359

template<class T> FLOATING_POINT_PRECISION
divide_by_1000(T v) {
  return static_cast<FLOATING_POINT_PRECISION>(v) / 1000.0;
}

namespace acc
{
  auto flight_time_read_conv = [] (int v) -> int { // [s]
    return v;
  };

  auto battery_voltage_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [V]
    return divide_by_1000(v);
  };

  auto hl_cpu_load_read_conv = [] (int v) -> int { // [Hz]
    return v;
  };

  auto hl_up_time_read_conv = [] (int v) -> int { // [s]
    return v;
  };

  auto motor_rpm_read_conv = [] (int v) -> int { // [rpm] (rouds per minute)
    return v * 64;
  };

  auto gps_lat_long_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [°]
    return v / 1E7;
  };

  auto gps_height_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [m]
    return divide_by_1000(v);
  };

  auto gps_speed_xy_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [m/s]
    return divide_by_1000(v);
  };

  auto gps_heading_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [°]
    return divide_by_1000(v);
  };

  auto gps_accuracy_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [m] [m/s]
    return divide_by_1000(v);
  };

  auto gps_general_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [m] [m/s]
    return divide_by_1000(v);
  };

  auto angvel_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [°/sec]
    return v * 0.0154;
  };

  auto acc_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [g]
    return v / 10000.0;
  };

  auto h_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // (earth magnetic field strength)
    return v / 2500.0;
  };

  auto angle_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [°]
    return divide_by_1000(v);
  };

  auto fusion_lat_long_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [°]
    return v / 1E7;
  };

  auto fusion_h_dh_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [m]
    return divide_by_1000(v);
  };

  auto fusion_speed_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [m/s]
    return divide_by_1000(v);
  };

  auto rc_channel_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [normalized] (0-1)
    return v / 4095.0;
  };

  auto deg2rad = [] (FLOATING_POINT_PRECISION v) -> FLOATING_POINT_PRECISION { // rad
    return v * PI/180.0;
  };

  auto rad2deg = [] (FLOATING_POINT_PRECISION v) -> FLOATING_POINT_PRECISION { // deg
    return v / (PI/180.0);
  };

  /*_      ______  ________________
  | |     / / __ \/  _/_  __/ ____/
  | | /| / / /_/ // /  / / / __/
  | |/ |/ / _, _// /  / / / /___
  |__/|__/_/ |_/___/ /_/ /_____/
  */
  auto DIMC_motor_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [rpm] (rouds per minute)
    if(v <= MOTOR_MIN_ROTATION_SPEED) {
      // throw std::runtime_error("it is not possible to set RPM lower than 1075"); // TODO Fix me decide a strategy
      return 0;
    } else if(v > MOTOR_MAX_ROTATION_SPEED) {
      // throw std::runtime_error("it is not possible to set RPM higher than 8600"); // TODO Fix me
      return 200;
    }
    return std::ceil((v - MOTOR_MIN_ROTATION_SPEED) / 37.625);
  };

  auto DMC_angles_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [normalized] (-1-1)
    FLOATING_POINT_PRECISION max = 1.0; //
    if(v < -max) {
      // throw std::runtime_error("it is not possible to set a DMC pithc or roll lower than " + std::to_string(-max));
      return 0;
    } else if(v > max) {
      // throw std::runtime_error("it is not possible to set a DMC pithc or roll higher than " + std::to_string(max));
      return 200;
    }
    return (v*100+100)/(max);
  };

  auto DMC_thrust_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [normalized] (0-1)
    FLOATING_POINT_PRECISION max = 1.0;
    if(v < 0) {
      // throw std::runtime_error("it is not possible to set a DMC thrust lower than " + std::to_string(0));
      return 0;
    } else if(v > max) {
      // throw std::runtime_error("it is not possible to set a DMC thrust higher than " + std::to_string(max));
      return 200;
    }
    return (v*200)/(max);
  };

  auto CTRL_pitch_roll_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [°]
    FLOATING_POINT_PRECISION max = 51.2; // or 52.0?
    if(v < -max) {
      // throw std::runtime_error("it is not possible to set a pitch or roll angle lower than " + std::to_string(-max));
      return(-2047);
    } else if(v > max) {
      // throw std::runtime_error("it is not possible to set a pitch or roll angle higher than " + std::to_string(max));
      return(2047);
    }
    return (v*2047)/max;          // v is [°] here
  };

  auto CTRL_yaw_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [°/sec]
    FLOATING_POINT_PRECISION max = 200.0; //
    if(v < -max) {
      // throw std::runtime_error("it is not possible to set a yaw rate lower than " + std::to_string(-max));
      return(-2047);
    } else if(v > max) {
      // throw std::runtime_error("it is not possible to set a yaw rate higher than " + std::to_string(max));
      return(2047);
    }
    return (v*2047)/max;          // v is [°/s] here
  };

  auto CTRL_thrust_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [normalized] (0-1)
    FLOATING_POINT_PRECISION max = 1.0;
    if(v < 0) {
      // throw std::runtime_error("it is not possible to set a thrust lower than " + std::to_string(0));
      return(0);
    } else if(v > max) {
      // throw std::runtime_error("it is not possible to set a thrust higher than " + std::to_string(max));
      return(4095);
    }
    return (v*4095)/max;
  };


  /* _____ ____  ___    ____  ______
    / ___// __ \/   |  / __ \/ ____/
    \__ \/ /_/ / /| | / /_/ / __/
   ___/ / ____/ ___ |/ _, _/ /___
  /____/_/   /_/  |_/_/ |_/_____/
  */

  inline std::array<FLOATING_POINT_PRECISION, 4>
  rpy2quaternion(std::array<FLOATING_POINT_PRECISION, 3> rpy) {
    std::array<FLOATING_POINT_PRECISION, 4> q = {{0,0,0,0}}; // q = [eta, epsilon1, epsilon2, epsilon3]
    q[0] = cos(rpy[0]/2) * cos(rpy[1]/2) * cos(rpy[2]/2) + sin(rpy[0]/2) * sin(rpy[1]/2) * sin(rpy[2]/2);
    q[1] = sin(rpy[0]/2) * cos(rpy[1]/2) * cos(rpy[2]/2) - cos(rpy[0]/2) * sin(rpy[1]/2) * sin(rpy[2]/2);
    q[2] = cos(rpy[0]/2) * sin(rpy[1]/2) * cos(rpy[2]/2) + sin(rpy[0]/2) * cos(rpy[1]/2) * sin(rpy[2]/2);
    q[3] = cos(rpy[0]/2) * cos(rpy[1]/2) * sin(rpy[2]/2) - sin(rpy[0]/2) * sin(rpy[1]/2) * cos(rpy[2]/2);
    // normalization
    auto q_norm = sqrt(pow(q[0], 2) + pow(q[1], 2) + pow(q[2], 2) + pow(q[3], 2));
    for(auto &qq:q) qq /= q_norm;
    return q;
  }
}

#endif // __cplusplus
#endif // _ACI_COMM_CONVERSION_LAMBDA_HPP_
