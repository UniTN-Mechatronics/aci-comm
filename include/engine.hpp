#ifndef _ACI_COMM_ENGINE_HPP_
#define _ACI_COMM_ENGINE_HPP_
#ifdef __cplusplus

#include <thread>
#include <atomic>
#include <iostream>
#include <assert.h>

#ifndef _ACI_COMM_BUS_HPP_
    #include "bus.hpp"
#endif
#ifndef _ACI_COMM_PACKET_HPP_
    #include "packet.hpp"
#endif
#ifndef _SEMAPHORE_HPP_
    #include "semaphore.hpp"
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
    *    Singleton class.
    *
    *    This class is NOT thread safe:
    *    you must use it from only ONE thread.
    */      
    class Engine
    {
    public:
        Bus *bus; // TODO: replace to unique_pointer
        Packet *packet = NULL; // TODO: replace to unique_pointer

        /**
        *   Singleton constructor
        */
        static Engine& init(Bus *bus_);     

        /**
        *   Deleted copy constructor and
        *   copy operator.
        */
        Engine(Engine const&) = delete;
        void operator=(Engine const&) = delete;
        
        /**
        *   Start port setup,
        *   start threads ecc..
        */
        void start();

        /**
        *   Join the aci_thread to
        *   the main thread.
        */
        void stop();
        
        void read() {
            assert("Function not implemented yet!");
        }
        void write() {
            assert("Function not implemented yet!");
        }

    private:
        /**
        *   Private constructor.
        */
        Engine(Bus *bus_) 
            : bus(bus_), 
            _aci_thread_run(false),
            _aci_thread_sem(1) {};

        /**
        *   Private destructor.
        */
        ~Engine() { stop(); }
        
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
        *   Not used yet.
        */
        Semaphore _aci_thread_sem;

        /**
        *   Setup the thread.
        */
        void _launch_aci_thread();

        /**
        *   Thread main loop method.
        */
        void _aci_thread_runner();
    };


}; // End namespace

#endif // __cplusplus
#endif // _ACI_COMM_ENGINE_HPP_
