#include "engine.hpp"
#include "commons.hpp"

void versions(struct ACI_INFO);
void transmit(void* byte, unsigned short cnt);

/**
*   [TEMP]
*/
int *global_port_ptr = NULL;

/*
*       _    ____ ___ 
*      / \  |  _ \_ _|
*     / _ \ | |_) | | 
*    / ___ \|  __/| | 
*   /_/   \_\_|  |___|
*   
*/
acc::Engine& 
acc::Engine::init(Bus *bus_) {
    static acc::Engine instance(bus_);
    return instance;
}

void 
acc::Engine::start() {
    if (_aci_thread_run) return;
    if (packet == NULL) throw std::runtime_error("packet is NOT set");
    try {
        bus->open();
        global_port_ptr = &bus->_port_state;
        aciInit();
        aciSetSendDataCallback(&transmit);
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
    std::cout << "Thread launch" << std::endl;
    int result = 0;
    unsigned char data = 0;
    while (_aci_thread_run) {
        result = ::read(bus->_port_state, &data, 1);
        while (result!=-1) {
            aciReceiveHandler(data);
            result = ::read(bus->_port_state, &data, 1);
        }
        aciEngine();
        usleep(10000);
    }
}

void 
transmit(void* byte, unsigned short cnt) {
    unsigned char *tbyte = (unsigned char *)byte;
    for (int i = 0; i < cnt; i++) {
        write(*global_port_ptr, &tbyte[i], 1);
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