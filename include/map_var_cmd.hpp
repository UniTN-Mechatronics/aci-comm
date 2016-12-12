#ifndef _ACI_COMM_MAP_VAR_CMD_HPP_
#define _ACI_COMM_MAP_VAR_CMD_HPP_
#ifdef __cplusplus

#include <map>
#include <string>
#include "drone_items.hpp"


namespace acc
{
    
    /**
    *   Singleton class.
    *   Currently, have an entire
    *   class only to build up 
    *   a map is an overhead:
    *   maybe in the future this class
    *   will make some other things, like
    *   read from json map file.
    */
    class MapVarCmd
    {
    public:

        static MapVarCmd& init(
            std::map<acc::ACI_COMM_VAR, DroneItemVar>& _map_var,
            std::map<acc::ACI_COMM_CMD, DroneItemCmd>& _map_cmd
        ) {
            static MapVarCmd mapVarCmd(_map_var, _map_cmd);
            return mapVarCmd;
        }

    private:

        /**
        *   Private constructor.
        */
        MapVarCmd(
            std::map<acc::ACI_COMM_VAR, DroneItemVar>& _map_var,
            std::map<acc::ACI_COMM_CMD, DroneItemCmd>& _map_cmd
        ) { 
            _alloc_map_var(_map_var);
            _alloc_map_cmd(_map_cmd);
        };

        /**
        *   Private destructor.
        */
        ~MapVarCmd() {};
        
        void _alloc_map_var(std::map<acc::ACI_COMM_VAR, DroneItemVar>& _map_var);
        void _alloc_map_cmd(std::map<acc::ACI_COMM_CMD, DroneItemCmd>& _map_cmd);

        /*  Maybe we will need them in future.
        *   std::map<std::string, DroneItem> _internal_map_var;
        *   std::map<std::string, DroneItem> _internal_map_cmd;
        */

    public:

        /**
        *   Deleted copy constructor and
        *   copy operator.
        */
        //MapVarCmd(MapVarCmd const&) delete;
        //void operator(MapVarCmd const&) delete;
    };
};

#endif // __cplusplus
#endif // _ACI_COMM_MAP_VAR_CMD_HPP_
