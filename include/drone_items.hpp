#ifndef _ACI_COMM_DRONE_ITEMS_HPP_   
#define _ACI_COMM_DRONE_ITEMS_HPP_   
#ifdef __cplusplus

#include <map>

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

    enum class DIP
    {
        READ = 0,
        WRITE
    };

    typedef acc::ACI_COMM_VAR Var;
    typedef acc::ACI_COMM_CMD Cmd;

    class DroneItemVar
    {
    public:
        DroneItemVar(ACI_COMM_VAR id, 
            int num_id, 
            DIP rw = DIP::READ, 
            int def_val = 0) : 
        _id(id),
        _num_id(num_id),
        _rw(rw),
        _value(def_val) {};
        DroneItemVar(const DroneItemVar& SB) {
            _id = SB._id;
            _num_id = SB._num_id;
            _rw = SB._rw;
            _value = SB._value;
            pck = SB.pck;
        };
        virtual ~DroneItemVar() {};

        ACI_COMM_VAR
        id() {
            return _id;
        }

        int
        num_id() {
            return _num_id;
        }

        int*
        value_ptr() {
            return &_value;
        }

        void
        set_value(int value) {
            _value = value;
        }

        bool
        can_be_read() {
            return _rw == DIP::READ;
        }

        bool
        can_be_written() {
            return _rw == DIP::WRITE;
        }

        int pck = 0;

    protected:
        ACI_COMM_VAR _id;
        int _num_id;
        DIP _rw;
        int _value;
    };

    class DroneItemCmd
    {
    public:
        DroneItemCmd(ACI_COMM_CMD id, 
            int num_id, 
            DIP rw = DIP::READ, 
            int def_val = 0) : 
        _id(id),
        _num_id(num_id),
        _rw(rw),
        _value(def_val) {};
        DroneItemCmd(const DroneItemCmd& SB) {
            _id = SB._id;
            _num_id = SB._num_id;
            _rw = SB._rw;
            _value = SB._value;
            pck = SB.pck;
        };
        virtual ~DroneItemCmd() {};

        ACI_COMM_CMD
        id() {
            return _id;
        }

        int
        num_id() {
            return _num_id;
        }

        int*
        value_ptr() {
            return &_value;
        }

        void
        set_value(int value) {
            _value = value;
        }

        bool
        can_be_read() {
            return _rw == DIP::READ;
        }

        bool
        can_be_written() {
            return _rw == DIP::WRITE;
        }

        int pck = 0;

    protected:
        ACI_COMM_CMD _id;
        int _num_id;
        DIP _rw;
        int _value;
    };

};



#endif // __cplusplus
#endif // _ACI_COMM_DRONE_ITEMS_HPP_ 
