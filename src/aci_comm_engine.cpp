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

#include "aci_comm_engine.hpp"

/*
*   C API Callbacks
*   They must be global, in order to be 
*   set in the API-C.
*/
static void c_api_transmit_callback(void*, unsigned short);
static void c_api_versions_callback(struct ACI_INFO);
static void c_api_reads_callback(void);
static void c_api_writes_callback(void);
static void c_api_params_callback(void);

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
    *   the *transmit* callback.
    *   Pointing at the Bus member
    *   variable.
    */
    int *_bus_port          = NULL;
    int _version_callback   = 0;
    int _reads_callback     = 0;
    int _writes_callback    = 0;
    int _reads_update_val   = 1; // TODO the upd freq is 1000/_reads_update_val
    MapVarItem _requested_vars;
    MapCmdItem _requested_cmds;
}


/*
*    _____             _            _____
*   | ____|_ __   __ _(_)_ __   ___|  ___|   _ _ __   ___ ___
*   |  _| | '_ \ / _` | | '_ \ / _ \ |_ | | | | '_ \ / __/ __|
*   | |___| | | | (_| | | | | |  __/  _|| |_| | | | | (__\__ \
*   |_____|_| |_|\__, |_|_| |_|\___|_|   \__,_|_| |_|\___|___/
*                |___/
*
*/
template<class BUS> void
acc::Engine<BUS>::start(int ep1, int ep2) {
    if (_aci_thread_run)
        throw std::runtime_error("Engine is already started!");

    if (ep1 < 0 || ep2 < 0)
        throw std::runtime_error("Ep1 and Ep2 must be positive integers!");

    if (_requested_vars.empty() && _requested_cmds.empty())
        throw std::runtime_error("Neither reads or writes are set!");

    try {
        // Used for return if callbacks don't comes.
        Timer timer;

        // Open bus.
        _bus.open();
        _bus_port = &_bus._port_state;
        aciInit();

        // Callbacks
        aciSetSendDataCallback(&c_api_transmit_callback);              // Transmit
        aciInfoPacketReceivedCallback(&c_api_versions_callback);       // Version
        aciSetVarListUpdateFinishedCallback(&c_api_reads_callback);    // Read
        aciSetCmdListUpdateFinishedCallback(&c_api_writes_callback);   // Write
        aciSetParamListUpdateFinishedCallback(&c_api_params_callback); // Params

        // Set engine and start thread.
        aciSetEngineRate(ep1, ep2);
        _launch_aci_thread(std::floor(1000000 / ep1));

        // Version
        _wait_on_version_callback(timer);

        // Read
        _wait_on_read_callback(timer);

        // Write
        _wait_on_write_callback(timer);

    } catch (std::runtime_error e) {
        throw e;
    }
}

template<class BUS> void
acc::Engine<BUS>::stop() {
    if (!_aci_thread_run)
        return;

    _aci_thread_run = false;
    _aci_thread.join();
    _requested_vars.clear();
    _requested_cmds.clear();
    _version_callback = 0;
    _reads_callback   = 0;
    _writes_callback  = 0;
}

template<class BUS> void
acc::Engine<BUS>::_launch_aci_thread(int time_sleep) {
    _aci_thread_run = true;
    _aci_thread = std::thread(&acc::Engine<BUS>::_aci_thread_runner, this, time_sleep);
}

template<class BUS> void
acc::Engine<BUS>::_aci_thread_runner(int time_sleep) {
    while (_aci_thread_run) {
        _aci_thread_runner_func(); 
        usleep(time_sleep);  
    }
    _aci_thread_runner_func();  
    usleep(time_sleep);
}

template<class BUS> void
acc::Engine<BUS>::_add_read(int pck, acc::Var key_read) {
    if (_aci_thread_run) throw std::runtime_error("Engine is running, you cannot add reads");
    MapVarItem::iterator it;
    it = _map_var.find(key_read);
    MapVarItem::iterator it2;
    it2 = _requested_vars.find(key_read);
    if (it2 != _requested_vars.end()) {
        int key_read_index = static_cast<std::underlying_type<acc::Var>::type>(key_read);
        throw std::runtime_error("This entry read key is already requested: " + DroneVarCmdToString::string_for_var_at_index(key_read_index));
    }
    _requested_vars.insert(std::make_pair(key_read, it->second));
    it2 = _requested_vars.find(key_read);
    it2->second.pck = pck;
}

template<class BUS> void
acc::Engine<BUS>::_add_write(int pck, acc::Cmd key_write) {
    if (_aci_thread_run) throw std::runtime_error("Engine is running, you cannot add writes");
    MapCmdItem::iterator it;
    it = _map_cmd.find(key_write);
    MapCmdItem::iterator it2;
    it2 = _requested_cmds.find(key_write);
    if (it2 != _requested_cmds.end()) {
        int write_read_index = static_cast<std::underlying_type<acc::Var>::type>(key_write);
        throw std::runtime_error("This entry write key not exist: " + DroneVarCmdToString::string_for_cmd_at_index(write_read_index));
    }
    _requested_cmds.insert(std::make_pair(key_write, it->second));
    it2 = _requested_cmds.find(key_write);
    it2->second.pck = pck;
}

template<class BUS> void
acc::Engine<BUS>::_aci_thread_runner_func() {
    int result = 0;
    unsigned char data = 0;
    result = ::read(_bus._port_state, &data, 1);
    while (result != -1) {
        aciReceiveHandler(data);
        result = ::read(_bus._port_state, &data, 1);
    }
    aciSynchronizeVars();
    aciEngine();
}

template<class BUS> long
acc::Engine<BUS>::read(acc::Var key_read) {
    for (MapVarItem::iterator it=_requested_vars.begin();
        it!=_requested_vars.end(); ++it)
    {
        if (it->first == key_read) {
            return it->second.get_cast_value();
        }
    }
    throw std::runtime_error("This entry read key not exist: ");
}

template<class BUS> void
acc::Engine<BUS>::write(acc::Cmd key_write, int value_write) {
    for (MapCmdItem::iterator it=_requested_cmds.begin();
        it!=_requested_cmds.end(); ++it)
    {
        if (it->first == key_write) {
            it->second.set_value(value_write);
            aciUpdateCmdPacket(it->second.pck);
            return;
        }
    }
    int value = static_cast<std::underlying_type<acc::Cmd>::type>(key_write);
    throw std::runtime_error("WRITE: This entry write key not exist: " + std::to_string(value) );
}

template<class BUS> void 
acc::Engine<BUS>::_wait_on_version_callback(Timer &timer) {
    aciCheckVerConf();
    while(!_version_callback) {
        if (timer.time() > _max_wait_time_seconds) return;
        usleep(1000);
    }
}

template<class BUS> void 
acc::Engine<BUS>::_wait_on_read_callback(Timer &timer) {
    if (!_requested_vars.empty()) {
        aciGetDeviceVariablesList();
        while(!_reads_callback) {
            if (timer.time() > _max_wait_time_seconds) return;
            usleep(1000);
        }
    }
}

template<class BUS> void 
acc::Engine<BUS>::_wait_on_write_callback(Timer &timer) {
    if (!_requested_cmds.empty()) {
        aciGetDeviceCommandsList();
        while(!_writes_callback) {
            if (timer.time() > _max_wait_time_seconds) return;
            usleep(1000);
        }
    }
}


/*
*     ____      _ _ _                _                   ____
*    / ___|__ _| | | |__   __ _  ___| | _____           / ___|
*   | |   / _` | | | '_ \ / _` |/ __| |/ / __|  _____  | |
*   | |__| (_| | | | |_) | (_| | (__|   <\__ \ |_____| | |___
*    \____\__,_|_|_|_.__/ \__,_|\___|_|\_\___/          \____|
*
*/
static void
c_api_transmit_callback(void* byte, unsigned short cnt)
{
    unsigned char *tbyte = (unsigned char *)byte;
    for (int i = 0; i < cnt; i++) {
        ::write(*_bus_port, &tbyte[i], 1);
    }
}

static void
c_api_versions_callback(struct ACI_INFO aciInfo) {
    printf("******************** Versions *******************\n");
    printf("* Type\t\t\tDevice\t\tRemote\t*\n");
    printf("* Major version\t\t%d\t=\t\%d\t*\n", aciInfo.verMajor,ACI_VER_MAJOR);
    printf("* Minor version\t\t%d\t=\t\%d\t*\n", aciInfo.verMinor,ACI_VER_MINOR);
    printf("* MAX_DESC_LENGTH\t%d\t=\t\%d\t*\n", aciInfo.maxDescLength,MAX_DESC_LENGTH);
    printf("* MAX_NAME_LENGTH\t%d\t=\t\%d\t*\n", aciInfo.maxNameLength,MAX_NAME_LENGTH);
    printf("* MAX_UNIT_LENGTH\t%d\t=\t\%d\t*\n", aciInfo.maxUnitLength,MAX_UNIT_LENGTH);
    printf("* MAX_VAR_PACKETS\t%d\t=\t\%d\t*\n", aciInfo.maxVarPackets,MAX_VAR_PACKETS);
    printf("*************************************************\n");
    _version_callback = 1;
}

static void
c_api_reads_callback() {
    std::vector<int> pkc_idx;
    for (MapVarItem::iterator it=_requested_vars.begin();
        it!=_requested_vars.end(); ++it)
    {
        pkc_idx.push_back(it->second.pck);
        aciAddContentToVarPacket(it->second.pck, it->second.num_id(), it->second.value_ptr());
    }
    std::sort(pkc_idx.begin(), pkc_idx.end());
    pkc_idx.erase(std::unique(pkc_idx.begin(), pkc_idx.end()), pkc_idx.end());
    for (auto &i : pkc_idx) {
        aciSetVarPacketTransmissionRate(i, _reads_update_val);
        aciVarPacketUpdateTransmissionRates();
        aciSendVariablePacketConfiguration(i);
    }
    _reads_callback = 1;
}

static void
c_api_writes_callback() {
    std::vector<int> pkc_idx;
    for (MapCmdItem::iterator it=_requested_cmds.begin();
        it!=_requested_cmds.end(); ++it)
    {
        pkc_idx.push_back(it->second.pck);
        aciAddContentToCmdPacket(it->second.pck, it->second.num_id(), it->second.value_ptr());
    }
    std::sort(pkc_idx.begin(), pkc_idx.end());
    pkc_idx.erase(std::unique(pkc_idx.begin(), pkc_idx.end()), pkc_idx.end());
    for (auto &i : pkc_idx) {
        aciSendCommandPacketConfiguration(i, 1);
        aciUpdateCmdPacket(i);
    }
    _writes_callback = 1;
}

static void
c_api_params_callback() {}

/*
*    _____         _____                _
*   | ____|_  ____|_   _| __ ___  _ __ | |
*   |  _| \ \/ / __|| || '_ ` _ \| '_ \| |
*   | |___ >  < (__ | || | | | | | |_) | |
*   |_____/_/\_\___||_||_| |_| |_| .__/|_|
*                                |_|
*
*/
/**
*   Explicit template instantiation.
*   MUST be kept at the end of this file,
*   don't move!
*/
#include "aci_comm_misc_explicits_templates.hpp"


//aciGetVarPacketRateFromDevice();
//aciSendParamLoad();
