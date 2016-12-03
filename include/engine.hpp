#ifndef _ACI_COMM_ENGINE_HPP_
#define _ACI_COMM_ENGINE_HPP_
#ifdef __cplusplus

#include <thread>
#include <atomic>
#include <iostream>
#include <tuple>
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
#ifndef _ACI_COMM_COMMONS_HPP_
    #include "commons.hpp"
#endif

void versions(struct ACI_INFO);

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

        template<class... BUS_ARGS>
        static Engine& init(BUS_ARGS... args_) {
            auto argst = std::tuple<BUS_ARGS...>(args_...);
            static Engine<BUS> engine(std::move(BUS(argst)));
            return engine;
        }

        /**
        *   Deleted copy constructor and
        *   copy operator.
        */
        Engine(Engine const&) = delete;
        void operator=(Engine const&) = delete;

        Bus
        bus() {
            return _bus;
        }
        
        void 
        set_packet(Packet *pck) {
            packet = pck;
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
        */
        void start();

        void stop();

        void 
        read() {
            assert("Function not implemented yet!");
        }

        void 
        write() {
            assert("Function not implemented yet!");
        }

    private:
        /**
        *   Private constructor.
        */
        Engine(BUS&& bus_) : 
            _bus(bus_), 
            _aci_thread_run(false),
            _aci_thread_sem(1) {};

        /**
        *   Private destructor.
        */
        ~Engine() { stop(); }

        BUS _bus;
        Packet *packet = NULL; 

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

        void _launch_aci_thread();
        void _aci_thread_runner();
    };

}; // End namespace

#endif // __cplusplus
#endif // _ACI_COMM_ENGINE_HPP_
