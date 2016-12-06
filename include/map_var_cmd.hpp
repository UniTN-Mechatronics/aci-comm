#ifndef _ACI_COMM_MAP_VAR_CMD_HPP_
#define _ACI_COMM_MAP_VAR_CMD_HPP_
#ifdef __cplusplus

#include <map>
#include <string>
#ifndef _ACI_COMM_DRONE_ITEMS_HPP_   
    #include "drone_items.hpp"
#endif

namespace acc
{
    /**
    *   Singleton class.
    */
    class MapVarCmd
    {
    public:

        static MapVarCmd& init() {
            static MapVarCmd mapVarCmd;
            return mapVarCmd;
        }

        std::map<std::string, DroneItem>
        get_map() { return _map_var_cmd; }

    private:

        /**
        *   Private constructor.
        */
        MapVarCmd() { _alloc_map_var_cmd(); };

        /**
        *   Private destructor.
        */
        ~MapVarCmd() {}

        std::map<std::string, DroneItem> _map_var_cmd;
        
        void _alloc_map_var_cmd();
        inline void _alloc_map_var();
        inline void _alloc_map_cmd();

    public:

        /**
        *   Deleted copy constructor and
        *   copy operator.
        */
        MapVarCmd(MapVarCmd const&) = delete;
        void operator=(MapVarCmd const&) = delete;
    };
};

#endif // __cplusplus
#endif // _ACI_COMM_MAP_VAR_CMD_HPP_
