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

#ifndef _ACI_COMM_ENGINE_HPP_
#define _ACI_COMM_ENGINE_HPP_
#ifdef __cplusplus

#include <thread>
#include <iostream>
#include <tuple>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <atomic>
#include <assert.h>

#include "bus.hpp"
#include "commons.hpp"
#include "map_var_cmd.hpp"
#include "uav_logger.hpp"

namespace acc
{

    /*
    *    _____             _
    *   | ____|_ __   __ _(_)_ __   ___
    *   |  _| | '_ \ / _` | | '_ \ / _ \
    *   | |___| | | | (_| | | | | |  __/
    *   |_____|_| |_|\__, |_|_| |_|\___|
    *                |___/
    *
    */
    /**
    *    Singleton class.
    *
    *    This class is NOT thread safe:
    *    you must use it from only ONE thread.
    */
    template<class BUS>
    class Engine
    {
    public:

        /**
        *   Singleton instace creator.
        *   Takes an arbitrary number
        *   of arguments, than wrap the args
        *   in a std::tuple, and call the private
        *   constructor with the BUS(argst).
        */
        template<class... BUS_ARGS>
        static Engine& init(BUS_ARGS... args_) {
            std::tuple<BUS_ARGS...> argst(args_...);
            static Engine<BUS> engine(std::move(BUS(argst)));
            return engine;
        }

        /**
        *   Deleted copy constructor and
        *   copy operator.
        */
        Engine(Engine const&) = delete;
        void operator=(Engine const&) = delete;

        /**
        *   Returns the pointer to
        *   the BUS instance.
        */
        BUS* bus() { return &_bus; }


        /**
        *   Add read variables.
        *   Variadic template form.
        */
        template<class Key, class... Args> void
        add_read(int pck, Key key_read, Args... args) {
            add_read(pck, key_read);
            add_read(pck, args...);
        }

        /**
        *   Add read variables.
        *   Variadic template form.
        */
        template<class... Args> void
        add_read(int pck, Args... args) {
            add_read(pck, args...);
        }

        /**
        *   @usage: Add read variable.
        *   @param
        *   
        */
        template<class Key> void
        add_read(int pck, Key key_read) {
            _add_read(pck, key_read);
        }

        /**
        *   Add commands.
        */
        template<class Key, class... Args> void
        add_write(int pck, Key key_write, Args... args) {
            add_write(pck, key_write);
            add_write(pck, args...);
        }

        template<class... Args> void
        add_write(int pck, Args... args) {
            add_write(pck, args...);
        }

        template<class Key> void
        add_write(int pck, Key key_write) {
            _add_write(pck, key_write);
        }

        /**
        *   Start port setup,
        *   start aci_thread,
        *   load the packet workload.
        *
        *   Throws when:
        *   * bus cannot be opened
        *   * the port confs cannot be applied
        *   * the packet is not setted
        *
        *   Return if time reach the 
        *   operation is done or
        *   *_max_wait_time_seconds* is reached.
        */
        void start(int ep1 = 100, int ep2 = 10);

        /**
        *   Join the aci_thread to the
        *   main thread.
        */
        void stop();

        /**
        *   Read variables.
        */
        template<class... Args> std::vector<int>
        read(Var key_read, Args... args) {
            std::vector<int> read_results;
            read_results.push_back( read(key_read) );
            read(read_results, args...);
            return read_results;
        }

        template<class... Args> void
        read(std::vector<int>& read_results,
             Var key_read, Args... args)
        {
            read_results.push_back(read(key_read));
            read(read_results, args...);
        }

        void
        read(std::vector<int>& read_results, Var key_read) {
            read_results.push_back(read(key_read));
        }

        int read(Var key_read);

        /**
        *   Write variables.
        */
        template<class... Args> void
        write(Cmd key_write, int value_write, Args... args) {
            write(key_write, value_write);
            write(args...);
        }

        void write(Cmd key_write, int value_write);

    private:
        int _max_wait_time_seconds = 20;

        Engine(BUS&& bus_) : _bus(bus_), _aci_thread_run(false) {
            MapVarCmd::init(_map_var, _map_cmd);
        };

        ~Engine() { 
            stop(); 
        }

        BUS _bus;

        /**
        *   The thread where the
        *   aci_callback lives.
        */
        std::thread _aci_thread;
        /**
        *   Flag used both as Engine state
        *   and as flag for thread loop exit.
        */
        std::atomic<bool> _aci_thread_run;

        /**
        *   The dictionary.
        */
        MapVarItem _map_var;
        MapCmdItem _map_cmd;

        void _launch_aci_thread(int time_sleep);
        void _aci_thread_runner(int time_sleep);
        void _aci_thread_runner_func();
        void _wait_on_version_callback(Timer &timer);
        void _wait_on_read_callback(Timer &timer);
        void _wait_on_write_callback(Timer &timer);
        void _add_read(int pck,  ACI_COMM_VAR key_read);
        void _add_write(int pck, ACI_COMM_CMD key_write);

    }; // End Engine<BUS>

}; // End namespace

#endif // __cplusplus
#endif // _ACI_COMM_ENGINE_HPP_
