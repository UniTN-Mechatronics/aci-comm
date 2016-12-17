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

#include "aci_comm_engine_map_var_cmd.hpp"
/*
*    _____                        ____  _          __  __ 
*   |  ___|   _ _ __  _ __  _   _/ ___|| |_ _   _ / _|/ _|
*   | |_ | | | | '_ \| '_ \| | | \___ \| __| | | | |_| |_ 
*   |  _|| |_| | | | | | | | |_| |___) | |_| |_| |  _|  _|
*   |_|   \__,_|_| |_|_| |_|\__, |____/ \__|\__,_|_| |_|  
*                           |___/                         
*/

/**
*   Macros in order to insert
*   var and cmd to the map.
*/
#define INSERT_VAR(id, cast, num_id) _map_var.insert(std::make_pair(id, acc::DroneItem<acc::Var>(id,  num_id, cast)))
#define INSERT_CMD(id, cast, num_id) _map_cmd.insert(std::make_pair(id, acc::DroneItem<acc::Cmd>(id,  num_id, cast, DIP::WRITE)))

/**
*   Variables.
*   INSERT NEW VARIABLES HERE.
*/
void 
acc::MapVarCmd::_alloc_map_var(MapVarItem& _map_var) {
    // 0x00xx: General system informations
    INSERT_VAR(acc::Var::UAV_status,            acc::intconv::cast_int16,  0x0001);
    INSERT_VAR(acc::Var::flight_time,           acc::intconv::cast_int16,  0x0002);
    INSERT_VAR(acc::Var::battery_voltage,       acc::intconv::cast_int16,  0x0003);
    INSERT_VAR(acc::Var::HL_cpu_load,           acc::intconv::cast_int16,  0x0004);
    INSERT_VAR(acc::Var::HL_up_time,            acc::intconv::cast_int16,  0x0005);
    // 0x01xx Sensor raw values
    INSERT_VAR(acc::Var::motor_rpm_1,           acc::intconv::cast_uint8,  0x0100);
    INSERT_VAR(acc::Var::motor_rpm_2,           acc::intconv::cast_uint8,  0x0101);
    INSERT_VAR(acc::Var::motor_rpm_3,           acc::intconv::cast_uint8,  0x0102);
    INSERT_VAR(acc::Var::motor_rpm_4,           acc::intconv::cast_uint8,  0x0103);
    INSERT_VAR(acc::Var::motor_rpm_5,           acc::intconv::cast_uint8,  0x0104);
    INSERT_VAR(acc::Var::motor_rpm_6,           acc::intconv::cast_uint8,  0x0105);
    INSERT_VAR(acc::Var::GPS_latitude,          acc::intconv::cast_int32,  0x0106);
    INSERT_VAR(acc::Var::GPS_longitude,         acc::intconv::cast_int32,  0x0107);
    INSERT_VAR(acc::Var::GPS_height,            acc::intconv::cast_int32,  0x0108);
    INSERT_VAR(acc::Var::GPS_speed_x,           acc::intconv::cast_int32,  0x0109);
    INSERT_VAR(acc::Var::GPS_speed_y,           acc::intconv::cast_int32,  0x010A);
    INSERT_VAR(acc::Var::GPS_heading,           acc::intconv::cast_int32,  0x010B);
    INSERT_VAR(acc::Var::GPS_position_accuracy, acc::intconv::cast_uint32, 0x010C);
    INSERT_VAR(acc::Var::GPS_height_accuracy,   acc::intconv::cast_uint32, 0x010D);
    INSERT_VAR(acc::Var::GPS_speed_accuracy,    acc::intconv::cast_uint32, 0x010E);
    INSERT_VAR(acc::Var::GPS_sat_num,           acc::intconv::cast_uint32, 0x010F);
    INSERT_VAR(acc::Var::GPS_status,            acc::intconv::cast_int32,  0x0110);
    INSERT_VAR(acc::Var::GPS_time_of_week,      acc::intconv::cast_uint32, 0x0111);
    INSERT_VAR(acc::ACI_COMM_VAR::GPS_week,     acc::intconv::cast_int32,  0x0112);
    // 0x02xx Sensor calibrated values
    INSERT_VAR(acc::Var::angvel_pitch,          acc::intconv::cast_int32,  0x0200);
    INSERT_VAR(acc::Var::angvel_roll,           acc::intconv::cast_int32,  0x0201);
    INSERT_VAR(acc::Var::angvel_yaw,            acc::intconv::cast_int32,  0x0202);
    INSERT_VAR(acc::Var::acc_x,                 acc::intconv::cast_int16,  0x0203);
    INSERT_VAR(acc::Var::acc_y,                 acc::intconv::cast_int16,  0x0204);
    INSERT_VAR(acc::Var::acc_z,                 acc::intconv::cast_int16,  0x0205);
    INSERT_VAR(acc::Var::Hx,                    acc::intconv::cast_int32,  0x0206);
    INSERT_VAR(acc::Var::Hy,                    acc::intconv::cast_int32,  0x0207);
    INSERT_VAR(acc::Var::Hz,                    acc::intconv::cast_int32,  0x0208);
    // 0x03xx Data-fused values
    INSERT_VAR(acc::Var::angle_pitch,           acc::intconv::cast_int32,  0x0300);
    INSERT_VAR(acc::Var::angle_roll,            acc::intconv::cast_int32,  0x0301);
    INSERT_VAR(acc::Var::angle_yaw,             acc::intconv::cast_int32,  0x0302);
    INSERT_VAR(acc::Var::fusion_latitude,       acc::intconv::cast_int32,  0x0303);
    INSERT_VAR(acc::Var::fusion_longitude,      acc::intconv::cast_int32,  0x0304);
    INSERT_VAR(acc::Var::fusion_dheight,        acc::intconv::cast_int32,  0x0305);
    INSERT_VAR(acc::Var::fusion_height,         acc::intconv::cast_int32,  0x0306);
    INSERT_VAR(acc::Var::fusion_speed_x,        acc::intconv::cast_int16,  0x0307);
    INSERT_VAR(acc::Var::fusion_speed_y,        acc::intconv::cast_int16,  0x0308);
    // 0x06xx User command values
    INSERT_VAR(acc::Var::RC_channel_0,          acc::intconv::cast_uint16, 0x0600);
    INSERT_VAR(acc::Var::RC_channel_1,          acc::intconv::cast_uint16, 0x0601);
    INSERT_VAR(acc::Var::RC_channel_2,          acc::intconv::cast_uint16, 0x0602);
    INSERT_VAR(acc::Var::RC_channel_3,          acc::intconv::cast_uint16, 0x0603);
    INSERT_VAR(acc::Var::RC_channel_4,          acc::intconv::cast_uint16, 0x0604);
    INSERT_VAR(acc::Var::RC_channel_5,          acc::intconv::cast_uint16, 0x0605);
    INSERT_VAR(acc::Var::RC_channel_6,          acc::intconv::cast_uint16, 0x0606);
    INSERT_VAR(acc::Var::RC_channel_7,          acc::intconv::cast_uint16, 0x0607);
}

/**
*   Commands.
*   INSERT NEW COMMANDS HERE.
*/
void 
acc::MapVarCmd::_alloc_map_cmd(MapCmdItem& _map_cmd) {
    INSERT_CMD(acc::Cmd::DIMC_motor_1,                 acc::intconv::cast_uint8, 0x0500);
    INSERT_CMD(acc::Cmd::DIMC_motor_2,                 acc::intconv::cast_uint8, 0x0501);
    INSERT_CMD(acc::Cmd::DIMC_motor_3,                 acc::intconv::cast_uint8, 0x0502);
    INSERT_CMD(acc::Cmd::DIMC_motor_4,                 acc::intconv::cast_uint8, 0x0503);
    INSERT_CMD(acc::Cmd::DIMC_motor_5,                 acc::intconv::cast_uint8, 0x0504);
    INSERT_CMD(acc::Cmd::DIMC_motor_6,                 acc::intconv::cast_uint8, 0x0505);
    INSERT_CMD(acc::Cmd::DMC_pitch,                    acc::intconv::cast_uint8, 0x0506);
    INSERT_CMD(acc::Cmd::DMC_roll,                     acc::intconv::cast_uint8, 0x0507);
    INSERT_CMD(acc::Cmd::DMC_yaw,                      acc::intconv::cast_uint8, 0x0508);
    INSERT_CMD(acc::Cmd::DMC_thrust,                   acc::intconv::cast_uint8, 0x0509);
    INSERT_CMD(acc::Cmd::CTRL_pitch,                   acc::intconv::cast_int16, 0x050A);
    INSERT_CMD(acc::Cmd::CTRL_roll,                    acc::intconv::cast_int16, 0x050B);
    INSERT_CMD(acc::Cmd::CTRL_yaw,                     acc::intconv::cast_int16, 0x050C);
    INSERT_CMD(acc::Cmd::CTRL_thrust,                  acc::intconv::cast_int16, 0x050D);
    INSERT_CMD(acc::Cmd::CTRL_ctrl,                    acc::intconv::cast_int16, 0x050E);
    INSERT_CMD(acc::Cmd::ctrl_mode,                    acc::intconv::cast_uint8, 0x0600);
    INSERT_CMD(acc::Cmd::ctrl_enabled,                 acc::intconv::cast_uint8, 0x0601);
    INSERT_CMD(acc::Cmd::disable_motor_onoff_by_stick, acc::intconv::cast_uint8, 0x0602);
}
