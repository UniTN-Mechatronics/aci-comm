#include "map_var_cmd.hpp"
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
#define INSERT_VAR(id, num_id) _map_var_cmd.insert(std::make_pair(id, acc::DroneItem(id,  num_id)))
#define INSERT_CMD(id, num_id) _map_var_cmd.insert(std::make_pair(id, acc::DroneItem(id,  num_id, DIP::WRITE)))

void 
acc::MapVarCmd::_alloc_map_var_cmd() {
    _alloc_map_var();
    _alloc_map_cmd();
}

/**
*   Variables.
*   INSERT NEW VARIABLES HERE.
*/
inline void 
acc::MapVarCmd::_alloc_map_var() {
    INSERT_VAR("angle_pitch",   0x0300);
    INSERT_VAR("angle_roll",    0x0301);
    INSERT_VAR("angle_yaw",     0x0302);
}

/**
*   Commands.
*   INSERT NEW COMMANDS HERE.
*/
inline void 
acc::MapVarCmd::_alloc_map_cmd() {

}