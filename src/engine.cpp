#include "engine.hpp"
#include "commons.hpp"

void versions(struct ACI_INFO);

                                            
/**
*   Anonymous namespace for 
*   global variables, is the 
*   same as declaring static
*   variables.
*/
namespace  
{
    /**
    *   Pointer to the bus 
    *   port state. Used by 
    *   the *transmit* lambda.
    *   Pointing at the Bus member
    *   variable.
    */
    int *bus_port;   
}


acc::Engine& 
acc::Engine::init(Bus *bus_) {
    static acc::Engine engine(bus_);
    return engine;
}

acc::Engine& 
acc::Engine::init(Bus *bus_, Packet *packet_) {
    static acc::Engine engine(bus_);
    engine.set_packet(packet_);
    return engine;
}

void 
acc::Engine::start() {
    if (_aci_thread_run) return;
    if (packet == NULL) throw std::runtime_error("packet is NOT set");
    try {
        _bus->open();
        bus_port = &_bus->_port_state;
        aciInit();
        auto lb = [](void* byte, unsigned short cnt) -> void {
            unsigned char *tbyte = (unsigned char *)byte;
            for (int i = 0; i < cnt; i++) ::write(*bus_port, &tbyte[i], 1);
        };
        aciSetSendDataCallback(lb);
        aciInfoPacketReceivedCallback(&versions);
        aciSetEngineRate(100, 10);
        _launch_aci_thread();
        aciCheckVerConf();
    } catch (std::runtime_error e) {
        throw e;
    }
}

void 
acc::Engine::stop() {
    if (!_aci_thread_run) return;
    _aci_thread_run = false;
    _aci_thread.join();
}


/*
*    ____       _            _       
*   |  _ \ _ __(_)_   ____ _| |_ ___ 
*   | |_) | '__| \ \ / / _` | __/ _ \
*   |  __/| |  | |\ V / (_| | ||  __/
*   |_|   |_|  |_| \_/ \__,_|\__\___|
*                                    
*/
void 
acc::Engine::_launch_aci_thread() {
    _aci_thread_run = true;
    _aci_thread = std::thread(&acc::Engine::_aci_thread_runner, this);
}

void 
acc::Engine::_aci_thread_runner() {
    int result = 0;
    unsigned char data = 0;
    while (_aci_thread_run) {
        result = ::read(_bus->_port_state, &data, 1);
        while (result!=-1) {
            aciReceiveHandler(data);
            result = ::read(_bus->_port_state, &data, 1);
        }
        aciEngine();
        usleep(10000);
    }
}






void versions(struct ACI_INFO aciInfo) {
    printf("******************** Versions *******************\n");
    printf("* Type\t\t\tDevice\t\tRemote\t*\n");
    printf("* Major version\t\t%d\t=\t\%d\t*\n",aciInfo.verMajor,ACI_VER_MAJOR);
    printf("* Minor version\t\t%d\t=\t\%d\t*\n",aciInfo.verMinor,ACI_VER_MINOR);
    printf("* MAX_DESC_LENGTH\t%d\t=\t\%d\t*\n",aciInfo.maxDescLength,MAX_DESC_LENGTH);
    printf("* MAX_NAME_LENGTH\t%d\t=\t\%d\t*\n",aciInfo.maxNameLength,MAX_NAME_LENGTH);
    printf("* MAX_UNIT_LENGTH\t%d\t=\t\%d\t*\n",aciInfo.maxUnitLength,MAX_UNIT_LENGTH);
    printf("* MAX_VAR_PACKETS\t%d\t=\t\%d\t*\n",aciInfo.maxVarPackets,MAX_VAR_PACKETS);
    printf("*************************************************\n");
}