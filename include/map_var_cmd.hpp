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
            MapVarItem& _map_var,
            MapCmdItem& _map_cmd
        ) {
            static MapVarCmd mapVarCmd(_map_var, _map_cmd);
            return mapVarCmd;
        }

    private:

        /**
        *   Private constructor.
        */
        MapVarCmd(
            MapVarItem& _map_var,
            MapCmdItem& _map_cmd
        ) { 
            _alloc_map_var(_map_var);
            _alloc_map_cmd(_map_cmd);
        };

        /**
        *   Private destructor.
        */
        ~MapVarCmd() {};
        
        void _alloc_map_var(MapVarItem& _map_var);
        void _alloc_map_cmd(MapCmdItem& _map_cmd);

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
