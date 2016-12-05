#ifndef _ACI_DRONE_ITEMS_HPP_	
#define _ACI_DRONE_ITEMS_HPP_	
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

	private:
		std::string _id;
		int _num_id;
		DIP _rw;
		int _value;
	};

};



#endif // __cplusplus
#endif // _ACI_DRONE_ITEMS_HPP_	
