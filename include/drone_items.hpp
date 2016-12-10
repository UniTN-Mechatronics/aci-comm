#ifndef _ACI_COMM_DRONE_ITEMS_HPP_   
#define _ACI_COMM_DRONE_ITEMS_HPP_   
#ifdef __cplusplus

#include <map>

namespace acc
{

    enum class DIP
    {
        READ = 0,
        WRITE
    };

    class DroneItem
    {
    public:
        DroneItem(std::string id, 
            int num_id, 
            DIP rw = DIP::READ, 
            int def_val = 0) : 
        _id(id),
        _num_id(num_id),
        _rw(rw),
        _value(def_val) {};
        DroneItem(const DroneItem& SB) {
            _id = SB._id;
            _num_id = SB._num_id;
            _rw = SB._rw;
            _value = SB._value;
            pck = SB.pck;
        };
        virtual ~DroneItem() {};

        std::string 
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
        std::string _id;
        int _num_id;
        DIP _rw;
        int _value;
    };

    class CompoundDroneItem {
    public:
        CompoundDroneItem(std::string name) {

        }

    private:
        std::map<std::string, DroneItem> _items;

    };

};



#endif // __cplusplus
#endif // _ACI_COMM_DRONE_ITEMS_HPP_ 
