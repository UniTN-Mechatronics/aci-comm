#ifndef _ACI_COMM_PACKET_HPP_
#define _ACI_COMM_PACKET_HPP_
#ifdef __cplusplus

#include <functional>

namespace acc 
{

    class Packet
    {
    public:
        template<class F, class... Args>
        Packet(F&& f, Args... args) {
            func = f;
        };
        virtual ~Packet() {};

        template<class F, class... Args> void 
        set_workload(F&& f, Args... args) {
            func = f;
        }
        
        std::function<void()> func;
    };

    class PacketInfo
    {
    public:


    };

};



#endif // __cplusplus
#endif // _ACI_COMM_PACKET_HPP_
