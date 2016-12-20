#ifndef _MB_SYNCRONIZER_HPP_
#define _MB_SYNCRONIZER_HPP_
#ifdef __cplusplus

#include <fstream>
#include <iostream>
#include <ostream>
#include <utility>
#include <iomanip>
#include <chrono>
#include <thread>

    /*   _______  ___   ____________  ____  _   ___________   __________
    *   / ___/\ \/ / | / / ____/ __ \/ __ \/ | / /  _/__  /  / ____/ __ \
    *   \__ \  \  /  |/ / /   / /_/ / / / /  |/ // /   / /  / __/ / /_/ /
    *  ___/ /  / / /|  / /___/ _, _/ /_/ / /|  // /   / /__/ /___/ _, _/
    * /____/  /_/_/ |_/\____/_/ |_|\____/_/ |_/___/  /____/_____/_/ |_|
    */  
namespace mb
{

    class Syncronizer
    {
    public:
        Syncronizer(double frequency) {
            _period_ns = static_cast<unsigned long>(1E9 / frequency);
            //std::cout << "_period_ns = " << _period_ns << std::endl;
        }

        void
        start() {
            _last_start = std::chrono::high_resolution_clock::now();
        }

        bool
        stop() {
            _last_stop = std::chrono::high_resolution_clock::now();

            auto _tet = std::chrono::duration_cast<std::chrono::nanoseconds>(_last_stop - _last_start);
            auto _nsec_to_wait = _period_ns - _tet.count();
            //std::cout << "_nsec_to_wait = " << _nsec_to_wait << std::endl;

            if(_nsec_to_wait < 0) {
                return false;
            }

            // VA
            while(true) {
                auto ct = std::chrono::high_resolution_clock::now();
                auto tet = std::chrono::duration_cast<std::chrono::nanoseconds>(ct - _last_start);
                auto nsec_to_wait = _period_ns - tet.count();
                if(nsec_to_wait < 0) {
                    return true;
                }
            }
        }

    private:
        long long _period_ns;
        std::chrono::high_resolution_clock::time_point _last_start;
        std::chrono::high_resolution_clock::time_point _last_stop;

    };


  double
  signal_builder(double time) {
    // signal features
    double period = 3.0;
    double min_value = 1100;
    double increment = 600;
    double max_value = 8600;
    
    // aux signals
    static double timer  = 0.0;
    static int conunter = 0;
    static int square = 0;
    static double signal_aux = 0;

    timer = time - period*conunter;

    if(timer >= period) {
    timer = 0.0;
    conunter++;
    
    square = conunter % 2;
    
    signal_aux += square * increment;
    std::cout << "signal_aux = " << signal_aux << std::endl;
    }

    double signal = signal_aux*square + min_value;

    if(signal > max_value) signal = min_value;

    return signal;

  }
}

#endif // __cplusplus
#endif // _MB_SYNCRONIZER_HPP_
