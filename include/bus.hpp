#ifndef _ACI_COMM_BUS_HPP_
#define _ACI_COMM_BUS_HPP_
#ifdef __cplusplus

#include <string>
#include <iostream>

namespace acc 
{
    class Engine;

    class Bus
    {
    public:
        friend class Engine;

        Bus() {};
        virtual ~Bus() {};

    protected:
        virtual void open() = 0;
        virtual void close() = 0;
    };


    class SerialBus: public Bus
    {
    public:
        SerialBus(std::string port) : _port(port) {};
        ~SerialBus() {};

    protected:
        virtual void open() final;
        virtual void close() final;

    private:
        std::string _port;
    };

};



#endif // __cplusplus
#endif // _ACI_COMM_BUS_HPP_
