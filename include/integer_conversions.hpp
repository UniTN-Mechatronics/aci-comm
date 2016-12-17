#ifndef _ACI_COMM_INTEGER_CONVERSIONS_HPP_
#define _ACI_COMM_INTEGER_CONVERSIONS_HPP_
#ifdef __cplusplus
#include <functional>
#include <cstdint>

/*
*	<cstdint> does not guarantee that
*	your implementation will put the
*	std:: symbols in the global namespace,
*	so, to be sure, is better to do it.
*/
using uint8_t 	= std::uint8_t;
using uint16_t 	= std::uint16_t;
using uint32_t 	= std::uint32_t;
using int16_t 	= std::int16_t;
using int32_t 	= std::int32_t;

namespace acc 
{
	/**
	*	Each drone item contains one of the
	*	following conversion function, in order
	*	to statically cast to the correct type.
	*/
	namespace intconv 
	{
		/** Cast int to uint8 */ 
		static std::function<int(int)> 
		cast_uint8 = [](int val) -> int {
    		return static_cast<uint8_t>(val);
		};

		/** Cast int to uint16 */ 
		static std::function<int(int)> 
		cast_uint16 = [](int val) -> int {
		    return static_cast<uint16_t>(val);
		};

		/** Cast int to int16 */ 
		static std::function<int(int)>
		cast_int16 = [](int val) -> int {
		    return static_cast<int16_t>(val);
		};
		
		/** Cast int to uint32 */ 
		static std::function<int(int)> 
		cast_uint32 = [](int val) -> int {
		    return static_cast<uint32_t>(val);
		};
		
		/** Cast int to int32 */ 
		static std::function<int(int)> 
		cast_int32 = [](int val) -> int {
		    return static_cast<int32_t>(val);
		};
	};
};

#endif // __cplusplus
#endif // _ACI_COMM_INTEGER_CONVERSIONS_HPP_
