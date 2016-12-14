#ifndef _ACI_COMM_DRONE_ITEMS_HPP_   
#define _ACI_COMM_DRONE_ITEMS_HPP_   
#ifdef __cplusplus


#include <map>
#include "commons.hpp"

namespace acc
{
    enum class DIP
    {
        READ = 0,
        WRITE
    };

    class DroneItemVar
    {
    public:
        DroneItemVar(ACI_COMM_VAR id, 
            int num_id, 
            DIP rw = DIP::READ, 
            int def_val = 0) : 
        _id(id),
        _num_id(num_id),
        _rw(rw),
        _value(def_val) {};
        DroneItemVar(const DroneItemVar& SB) {
            _id = SB._id;
            _num_id = SB._num_id;
            _rw = SB._rw;
            _value = SB._value;
            pck = SB.pck;
        };
        virtual ~DroneItemVar() {};

        ACI_COMM_VAR
        id() {
            return _id;
        }

        int
        num_id() {
            return _num_id;
        }

        int*
        value_ptr() {
            return &_value;
        }

        void
        set_value(int value) {
            _value = value;
        }

        bool
        can_be_read() {
            return _rw == DIP::READ;
        }

        bool
        can_be_written() {
            return _rw == DIP::WRITE;
        }

        int pck = 0;

    protected:
        ACI_COMM_VAR _id;
        int _num_id;
        DIP _rw;
        int _value;
    };

    class DroneItemCmd
    {
    public:
        DroneItemCmd(ACI_COMM_CMD id, 
            int num_id, 
            DIP rw = DIP::WRITE, 
            int def_val = 0) : 
        _id(id),
        _num_id(num_id),
        _rw(rw),
        _value(def_val) {};
        DroneItemCmd(const DroneItemCmd& SB) {
            _id = SB._id;
            _num_id = SB._num_id;
            _rw = SB._rw;
            _value = SB._value;
            pck = SB.pck;
        };
        virtual ~DroneItemCmd() {};

        ACI_COMM_CMD
        id() {
            return _id;
        }

        int
        num_id() {
            return _num_id;
        }

        int*
        value_ptr() {
            return &_value;
        }

        void
        set_value(int value) {
            _value = value;
        }

        bool
        can_be_read() {
            return _rw == DIP::READ;
        }

        bool
        can_be_written() {
            return _rw == DIP::WRITE;
        }

        int pck = 0;

    protected:
        ACI_COMM_CMD _id;
        int _num_id;
        DIP _rw;
        int _value;
    };

};



#endif // __cplusplus
#endif // _ACI_COMM_DRONE_ITEMS_HPP_ 
