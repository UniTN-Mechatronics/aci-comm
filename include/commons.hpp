#ifndef _ACI_COMM_COMMONS_HPP_
#define _ACI_COMM_COMMONS_HPP_
#ifdef __cplusplus

namespace acc
{
    enum class ACI_COMM_VAR
    {                               // UAV READ CLASSES IMPLEMENTATION
        UAV_status             = 0, //
        flight_time            ,    //
        battery_voltage        ,    //
        HL_cpu_load            ,    //
        HL_up_time             ,    //
        motor_rpm_1            ,    // implemented, tested
        motor_rpm_2            ,    // implemented
        motor_rpm_3            ,    // implemented
        motor_rpm_4            ,    // implemented
        motor_rpm_5            ,    // implemented, impossible to test
        motor_rpm_6            ,    // implemented, impossible to test
        GPS_latitude           ,    //
        GPS_longitude          ,    //
        GPS_height             ,    //
        GPS_speed_x            ,    //
        GPS_speed_y            ,    //
        GPS_heading            ,    //
        GPS_position_accuracy  ,    //
        GPS_height_accuracy    ,    //
        GPS_speed_accuracy     ,    //
        GPS_sat_num            ,    //
        GPS_status             ,    //
        GPS_time_of_week       ,    //
        GPS_week               ,    //
        angvel_pitch           ,    // implemented
        angvel_roll            ,    // implemented
        angvel_yaw             ,    // implemented
        acc_x                  ,    // implemented
        acc_y                  ,    // implemented
        acc_z                  ,    // implemented
        Hx                     ,    // implemented
        Hy                     ,    // implemented
        Hz                     ,    // implemented
        angle_pitch            ,    // implemented, tested
        angle_roll             ,    // implemented, tested
        angle_yaw              ,    // implemented, tested
        fusion_latitude        ,    //
        fusion_longitude       ,    //
        fusion_dheight         ,    //
        fusion_height          ,    //
        fusion_speed_x         ,    //
        fusion_speed_y         ,    //
        RC_channel_0           ,    // implemented
        RC_channel_1           ,    // implemented
        RC_channel_2           ,    // implemented
        RC_channel_3           ,    // implemented
        RC_channel_4           ,    // implemented
        RC_channel_5           ,    // implemented
        RC_channel_6           ,    // implemented
        RC_channel_7                // implemented
    };

    enum class ACI_COMM_CMD
    {
        DIMC_motor_1                 = 0, // implemented, tested
        DIMC_motor_2                 ,    // implemented
        DIMC_motor_3                 ,    // implemented
        DIMC_motor_4                 ,    // implemented
        DIMC_motor_5                 ,    //
        DIMC_motor_6                 ,    //
        DMC_pitch                    ,    // implemented
        DMC_roll                     ,    // implemented
        DMC_yaw                      ,    // implemented
        DMC_thrust                   ,    // implemented
        CTRL_pitch                   ,    // implemented
        CTRL_roll                    ,    // implemented
        CTRL_yaw                     ,    // implemented
        CTRL_thrust                  ,    // implemented
        CTRL_ctrl                    ,    // implemented
        ctrl_mode                    ,    // implemented
        ctrl_enabled                 ,    // implemented
        disable_motor_onoff_by_stick      // implemented
    };

    typedef acc::ACI_COMM_VAR Var;
    typedef acc::ACI_COMM_CMD Cmd;

    enum class CTRL_MODE
    {
        DIMC = 0,
        DMC,
        CTRL,
        GPS,
        READ_ONLY
    };
}

extern "C" {
    #include "asctecCommIntf.h"
}

#endif // __cplusplus
#endif // _ACI_COMM_COMMONS_HPP_
