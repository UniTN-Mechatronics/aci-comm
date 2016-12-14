#ifndef _ACI_COMM_CONVERSION_LAMBDA_HPP_
#define _ACI_COMM_CONVERSION_LAMBDA_HPP_
#ifdef __cplusplus


#include <iostream> 

  auto flight_time_read_conv = [] (int v) -> int { // [s]
    return v;
  };

  auto battery_voltage_read_conv = [] (int v) -> double { // [V]
    return v / 1000.0;
  };

  auto HL_cpu_load_read_conv = [] (int v) -> int { // [Hz]
    return v;
  };

  auto HL_up_time_read_conv = [] (int v) -> int { // [s]
    return v;
  };

  auto motor_rpm_read_conv = [] (int v) -> int { // [rpm] (rouds per minute)
    return v * 64;
  };

  auto angvel_read_conv = [] (int v) -> double { // [°/sec]
    return v * 0.0154;
  };

  auto acc_read_conv = [] (int v) -> double { // [g]
    return v / 10000.0;
  };

  auto H_read_conv = [] (int v) -> double { // (earth magnetic field strength)
    return v / 2500.0;
  };

  auto angle_read_conv = [] (int v) -> double { // [°]
    return v / 1000.0;
  };

  auto RC_channel_read_conv = [] (int v) -> double { // [normalized] (0-1)
    return v / 4095.0;
  };

  /*_      ______  ________________
  | |     / / __ \/  _/_  __/ ____/
  | | /| / / /_/ // /  / / / __/
  | |/ |/ / _, _// /  / / / /___
  |__/|__/_/ |_/___/ /_/ /_____/
  */ 
  auto DIMC_motor_write_conv = [] (double v) -> int { // [rpm] (rouds per minute)
    if(v < 1075) {
      throw std::runtime_error("it is not possible to set RPM lower than 1075");
    } else if(v > 8600) {
      throw std::runtime_error("it is not possible to set RPM higher than 8600");
    }
    return (v - 1075) * 1/37.625;
  };

  auto DMC_angles_write_conv = [] (double v) -> int { // [normalized] (-1-1)
    double max = 1.0; //
    if(v < -max) {
      throw std::runtime_error("it is not possible to set a DMC pithc or roll lower than " + std::to_string(-max));
    } else if(v > max) {
      throw std::runtime_error("it is not possible to set a DMC pithc or roll higher than " + std::to_string(max));
    }
    return (v*100+100)/(max);
  };

  auto DMC_thrust_write_conv = [] (double v) -> int { // [normalized] (0-1)
    double max = 1.0;
    if(v < 0) {
      throw std::runtime_error("it is not possible to set a DMC thrust lower than " + std::to_string(0));
    } else if(v > max) {
      throw std::runtime_error("it is not possible to set a DMC thrust higher than " + std::to_string(max));
    }
    return (v*200)/(max);
  };

  auto CTRL_pitch_roll_write_conv = [] (double v) -> int { // [°]
    double max = 51.2; // or 52.0?
    if(v < -max) {
      throw std::runtime_error("it is not possible to set a pitch or roll angle lower than " + std::to_string(-max));
    } else if(v > max) {
      throw std::runtime_error("it is not possible to set a pitch or roll angle higher than " + std::to_string(max));
    }
    return (v*2047)/max;
  };

  auto CTRL_yaw_write_conv = [] (double v) -> int { // [°/sec]
    double max = 200.0; // or 52.0?
    if(v < -max) {
      throw std::runtime_error("it is not possible to set a yaw rate lower than " + std::to_string(-max));
    } else if(v > max) {
      throw std::runtime_error("it is not possible to set a yaw rate higher than " + std::to_string(max));
    }
    return (v*2047)/max;
  };

  auto CTRL_thrust_write_conv = [] (double v) -> int { // [normalized] (0-1)
    double max = 1.0; // or 52.0?
    if(v < 0) {
      throw std::runtime_error("it is not possible to set a thrust lower than " + std::to_string(0));
    } else if(v > max) {
      throw std::runtime_error("it is not possible to set a thrust higher than " + std::to_string(max));
    }
    return (v*4095)/max;
  };

#endif // __cplusplus
#endif // _ACI_COMM_CONVERSION_LAMBDA_HPP_
