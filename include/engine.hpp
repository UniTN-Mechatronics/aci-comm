#ifndef _ACI_COMM_ENGINE_HPP_
#define _ACI_COMM_ENGINE_HPP_
#ifdef __cplusplus

#include <iostream>

#ifndef _ACI_COMM_BUS_HPP_
    #include "bus.hpp"
#endif
#ifndef _ACI_COMM_PACKET_HPP_
    #include "packet.hpp"
#endif

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
    *    Singleton class
    */      
    class Engine
    {
    public:
        
        /**
        *   Singleton constructor
        */
        static Engine& create(Bus *bus_);
        
        void test();

        Bus *bus;

    private:
        Engine(Bus *bus_) : bus(bus_) {};

    public:
        /**
        *   Deleted copy constructor and
        *   copy operator.
        */
        Engine(Engine const&) = delete;
        void operator=(Engine const&) = delete;
    };


}; // End namespace

#endif // __cplusplus
#endif // _ACI_COMM_ENGINE_HPP_
