#ifndef _ACI_COMM_CONVERSION_LAMBDA_HPP_
#define _ACI_COMM_CONVERSION_LAMBDA_HPP_
#ifdef __cplusplus

#ifndef FLOATING_POINT_PRECISION
#define FLOATING_POINT_PRECISION double
#endif

#define PI 3.14159265359

// #define ANGLE_UNIT_RAD // if it is defined angle, angvel, ctrl_pitch/yaw/roll are in [rad] or [rad/s]


// TODO: for angles return rads not °

template<class T> FLOATING_POINT_PRECISION
divide_by_1000(T v) {
  return static_cast<FLOATING_POINT_PRECISION>(v)/1000.0;
}


#include <iostream>

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

  auto angvel_read_conv = [] (int v) -> FLOATING_POINT_PRECISION {
    #ifndef ANGLE_UNIT_RAD
    return v * 0.0154;            // [°/sec]
    #endif
    return v * 0.0154 * PI/180.0; // [rad/sec]
  };

  auto acc_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [g]
    return v / 10000.0;
  };

  auto h_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // (earth magnetic field strength)
    return v / 2500.0;
  };

  auto angle_read_conv = [] (int v) -> FLOATING_POINT_PRECISION { // [rad]
    #ifndef ANGLE_UNIT_RAD
    return divide_by_1000(v);            // [°]
    #endif
    return divide_by_1000(v) * PI/180.0; // [rad]
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

  /*_      ______  ________________
  | |     / / __ \/  _/_  __/ ____/
  | | /| / / /_/ // /  / / / __/
  | |/ |/ / _, _// /  / / / /___
  |__/|__/_/ |_/___/ /_/ /_____/
  */
  auto DIMC_motor_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [rpm] (rouds per minute)
    if(v < 1075) {
      throw std::runtime_error("it is not possible to set RPM lower than 1075");
      return 0;
    } else if(v > 8600) {
      throw std::runtime_error("it is not possible to set RPM higher than 8600");
      return 200;
    }
    return (v - 1075) * 1/37.625;
  };

  auto DMC_angles_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [normalized] (-1-1)
    FLOATING_POINT_PRECISION max = 1.0; //
    if(v < -max) {
      throw std::runtime_error("it is not possible to set a DMC pithc or roll lower than " + std::to_string(-max));
    } else if(v > max) {
      throw std::runtime_error("it is not possible to set a DMC pithc or roll higher than " + std::to_string(max));
    }
    return (v*100+100)/(max);
  };

  auto DMC_thrust_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [normalized] (0-1)
    FLOATING_POINT_PRECISION max = 1.0;
    if(v < 0) {
      throw std::runtime_error("it is not possible to set a DMC thrust lower than " + std::to_string(0));
    } else if(v > max) {
      throw std::runtime_error("it is not possible to set a DMC thrust higher than " + std::to_string(max));
    }
    return (v*200)/(max);
  };

  auto CTRL_pitch_roll_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [°] or [rad]
    FLOATING_POINT_PRECISION max = 51.2; // or 52.0?
    if(v < -max) {
      throw std::runtime_error("it is not possible to set a pitch or roll angle lower than " + std::to_string(-max));
    } else if(v > max) {
      throw std::runtime_error("it is not possible to set a pitch or roll angle higher than " + std::to_string(max));
    }
    #ifndef ANGLE_UNIT_RAD
    return (v*2047)/max;          // v is [°] here
    #endif
    return ((v*180/PI)*2047)/max; // v is [rad] here
  };

  auto CTRL_yaw_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [°/sec]
    FLOATING_POINT_PRECISION max = 200.0; //
    if(v < -max) {
      throw std::runtime_error("it is not possible to set a yaw rate lower than " + std::to_string(-max));
    } else if(v > max) {
      throw std::runtime_error("it is not possible to set a yaw rate higher than " + std::to_string(max));
    }
    #ifndef ANGLE_UNIT_RAD
    return (v*2047)/max;          // v is [°/s] here
    #endif
    return ((v*180/PI)*2047)/max; // v is [deg/s] here
  };

  auto CTRL_thrust_write_conv = [] (FLOATING_POINT_PRECISION v) -> int { // [normalized] (0-1)
    FLOATING_POINT_PRECISION max = 1.0;
    if(v < 0) {
      throw std::runtime_error("it is not possible to set a thrust lower than " + std::to_string(0));
    } else if(v > max) {
      throw std::runtime_error("it is not possible to set a thrust higher than " + std::to_string(max));
    }
    return (v*4095)/max;
  };

#endif // __cplusplus
#endif // _ACI_COMM_CONVERSION_LAMBDA_HPP_
