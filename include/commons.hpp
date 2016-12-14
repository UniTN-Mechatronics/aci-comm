#ifndef _ACI_COMM_COMMONS_HPP_
#define _ACI_COMM_COMMONS_HPP_
#ifdef __cplusplus

namespace acc 
{
    enum class ACI_COMM_VAR
    {
        UAV_status             = 0,
        flight_time            ,
        battery_voltage        ,
        HL_cpu_load            ,
        HL_up_time             ,
        motor_rpm_1            ,
        motor_rpm_2            ,
        motor_rpm_3            ,
        motor_rpm_4            ,
        motor_rpm_5            ,
        motor_rpm_6            ,
        GPS_latitude           ,
        GPS_longitude          ,
        GPS_height             ,
        GPS_speed_x            ,
        GPS_speed_y            ,
        GPS_heading            ,
        GPS_position_accuracy  ,
        GPS_height_accuracy    ,
        GPS_speed_accuracy     ,
        GPS_sat_num            ,
        GPS_status             ,
        GPS_time_of_week       ,
        GPS_week               ,
        angvel_pitch           ,
        angvel_roll            ,
        angvel_yaw             ,
        acc_x                  ,
        acc_y                  ,
        acc_z                  ,
        Hx                     ,
        Hy                     ,
        Hz                     ,
        angle_pitch            ,
        angle_roll             ,
        angle_yaw              ,
        fusion_latitude        ,
        fusion_longitude       ,
        fusion_dheight         ,
        fusion_height          ,
        fusion_speed_x         ,
        fusion_speed_y         ,
        RC_channel_0           ,
        RC_channel_1           ,
        RC_channel_2           ,
        RC_channel_3           ,
        RC_channel_4           ,
        RC_channel_5           ,
        RC_channel_6           ,
        RC_channel_7           
    };

    enum class ACI_COMM_CMD
    {
        DIMC_motor_1                 = 0, 
        DIMC_motor_2                 , 
        DIMC_motor_3                 , 
        DIMC_motor_4                 , 
        DIMC_motor_5                 , 
        DIMC_motor_6                 , 
        DMC_pitch                    , 
        DMC_roll                     , 
        DMC_yaw                      , 
        DMC_thrust                   , 
        CTRL_pitch                   , 
        CTRL_roll                    , 
        CTRL_yaw                     , 
        CTRL_thrust                  , 
        CTRL_ctrl                    , 
        ctrl_mode                    , 
        ctrl_enabled                 , 
        disable_motor_onoff_by_stick 
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







