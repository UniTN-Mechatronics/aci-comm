#include "engine.hpp"


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
    int version_callback = 0;
    int reads_callback = 0;
    std::map<std::string, acc::DroneItem> _requsted_vars;
}

                               
template<class BUS> void 
acc::Engine<BUS>::start() {
    if (_aci_thread_run) return;
    if (_requsted_vars.empty()) throw std::runtime_error("no reads set!");
    try {
        _bus.open(); // Can throw.
        bus_port = &_bus._port_state;
        version_callback = 0;
        reads_callback = 0;
        aciInit();
        aciSetSendDataCallback([](void* byte, unsigned short cnt) -> void {
            unsigned char *tbyte = (unsigned char *)byte;
            for (int i = 0; i < cnt; i++) {
                ::write(*bus_port, &tbyte[i], 1);
            }
        });
        
        // Version 
        aciInfoPacketReceivedCallback(&versions);

        // Read
        aciSetVarListUpdateFinishedCallback(&varListUpdateFinished);
        
        // Write
        //aciSetCmdListUpdateFinishedCallback(&cmdListUpdateFinished);

        aciSetEngineRate(100, 10);
        _launch_aci_thread();
        
        // Version
        aciCheckVerConf();
        while(!version_callback) usleep(1000);
        
        // Read
        aciGetDeviceVariablesList();
        while(!reads_callback) usleep(1000);

        usleep(1000);
        // Write
        //ciGetDeviceCommandsList();

        //while(!reads_callback) {};
        //_set_reads();

        //aciGetVarPacketRateFromDevice();
        //aciSendParamLoad();
    } catch (std::runtime_error e) {
        throw e;
    }
}

template<class BUS> void 
acc::Engine<BUS>::stop() {
    if (!_aci_thread_run) return;
    _aci_thread_run = false;
    _aci_thread.join();
}

template<class BUS> void 
acc::Engine<BUS>::_alloc_map_var_cmd() {
    _map_var_cmd.insert(std::make_pair("angle_pitch", DroneItem("angle_pitch",  0x0300)));
    _map_var_cmd.insert(std::make_pair("angle_roll",  DroneItem("angle_roll",   0x0301)));
    _map_var_cmd.insert(std::make_pair("angle_yaw",   DroneItem("angle_yaw",    0x0302)));
}

template<class BUS> void 
acc::Engine<BUS>::_launch_aci_thread() {
    _aci_thread_run = true;
    _aci_thread = std::thread(&acc::Engine<BUS>::_aci_thread_runner, this);
}
        
template<class BUS> void 
acc::Engine<BUS>::_aci_thread_runner() {
    int result = 0;
    unsigned char data = 0;
    while (_aci_thread_run) {
        result = ::read(_bus._port_state, &data, 1);
        while (result != -1) {
            aciReceiveHandler(data);
            result = ::read(_bus._port_state, &data, 1);
        }
        aciSynchronizeVars();
        aciEngine();
        usleep(10000);
    }
}

template<class BUS> void 
acc::Engine<BUS>::add_read(std::initializer_list<std::string> reads) {
    std::map<std::string, DroneItem>::iterator it;
    for (auto &r : reads) {
        it = _map_var_cmd.find(r);
        if (it == _map_var_cmd.end()) {
            throw std::runtime_error("This entry read key not exist: " + r);
        }
        _requsted_vars.insert(std::make_pair(r, it->second));
    }
}

template<class BUS> int 
acc::Engine<BUS>::read(std::string key_read) {
    std::cout << "Start read" << std::endl;
    for (std::map<std::string, DroneItem>::iterator it=_requsted_vars.begin(); 
        it!=_requsted_vars.end(); ++it) 
    {
        if (it->first == key_read) {
            return *it->second.value_ptr();
        }
    }
    throw std::runtime_error("This entry read key not exist: " + key_read);
}  

template<class BUS> void 
acc::Engine<BUS>::_set_reads() {
    std::cout << "set reads" << std::endl;
    for (std::map<std::string, DroneItem>::iterator it=_requsted_vars.begin(); 
        it!=_requsted_vars.end(); ++it) 
    {
        aciAddContentToVarPacket(0, it->second.num_id() , it->second.value_ptr()); 
    }
    aciSetVarPacketTransmissionRate(0, 10);
    aciVarPacketUpdateTransmissionRates();
    aciSendVariablePacketConfiguration(0);
}

void versions(struct ACI_INFO aciInfo) {
    printf("******************** Versions *******************\n");
    printf("* Type\t\t\tDevice\t\tRemote\t*\n");
    printf("* Major version\t\t%d\t=\t\%d\t*\n", aciInfo.verMajor,ACI_VER_MAJOR);
    printf("* Minor version\t\t%d\t=\t\%d\t*\n", aciInfo.verMinor,ACI_VER_MINOR);
    printf("* MAX_DESC_LENGTH\t%d\t=\t\%d\t*\n", aciInfo.maxDescLength,MAX_DESC_LENGTH);
    printf("* MAX_NAME_LENGTH\t%d\t=\t\%d\t*\n", aciInfo.maxNameLength,MAX_NAME_LENGTH);
    printf("* MAX_UNIT_LENGTH\t%d\t=\t\%d\t*\n", aciInfo.maxUnitLength,MAX_UNIT_LENGTH);
    printf("* MAX_VAR_PACKETS\t%d\t=\t\%d\t*\n", aciInfo.maxVarPackets,MAX_VAR_PACKETS);
    printf("*************************************************\n");
    version_callback = 1;
}

void 
varListUpdateFinished() {
    printf("variables updated\n");
    for (std::map<std::string, acc::DroneItem>::iterator it=_requsted_vars.begin(); 
        it!=_requsted_vars.end(); ++it) 
    {
        aciAddContentToVarPacket(0, it->second.num_id(), it->second.value_ptr()); 
    }
    aciSetVarPacketTransmissionRate(0,10);
    aciVarPacketUpdateTransmissionRates();
    aciSendVariablePacketConfiguration(0);
    reads_callback = 1;
    
    //printf("reads_callback: %d\n", reads_callback);
    //aciAddContentToVarPacket(0,0x0203, &acc_x);
    //aciSetVarPacketTransmissionRate(0,10);
    //aciVarPacketUpdateTransmissionRates();
    //aciSendVariablePacketConfiguration(0);
    //var_getted=1;
}

void 
cmdListUpdateFinished() {
    printf("command list getted!\n");
    /*aciAddContentToCmdPacket(0, 0x0500, &motor1);
    aciAddContentToCmdPacket(0, 0x0501, &motor2);
    aciAddContentToCmdPacket(0, 0x0502, &motor3);
    aciAddContentToCmdPacket(0, 0x0503, &motor4);
    aciAddContentToCmdPacket(1, 0x0600, &ctrl_mode);
    aciAddContentToCmdPacket(1, 0x0601, &ctrl_enabled);
    aciAddContentToCmdPacket(1, 0x0602, &disable_motor_onoff_by_stick);
    aciSendCommandPacketConfiguration(0, 0);
    aciSendCommandPacketConfiguration(1, 1);
    motor1 = 0;
    motor2 = 0;
    motor3 = 0;
    motor4 = 0;
    ctrl_mode=0;
    ctrl_enabled=1;
    disable_motor_onoff_by_stick = 1;
    aciUpdateCmdPacket(0);
    aciUpdateCmdPacket(1);
    cmd_ready=1;*/
}


/**
*   Explicit template instantiation.
*   MUST be kept at the end of this file,
*   don't move!
*/
#include "explicits_templates.hpp"







