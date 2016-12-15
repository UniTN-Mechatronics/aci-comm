#ifndef _ACI_COMM_UAV_LOGGER_HPP_
#define _ACI_COMM_UAV_LOGGER_HPP_
#ifdef __cplusplus

#include <fstream>
#include <iostream>
#include <ostream>
#include <tuple>
#include "aci_comm_uav.hpp"

namespace acc 
{/*
	class Logger 
	{
	public:
		friend class UAV;

		Logger(std::ostream *stream) {
			_stream = stream;
		}; 

		template<class T, class... Args> Logger&
		operator<<(T&&t, Args... args) {
			std::tuple<Args...> argst(args...);
			_stream << t;
			_print(argst);
			_stream << std::endl;
			return *this;
		}

		template<class T> Logger&
		operator<<(T&&t) {
			_stream << t;
			return *this;
		}

	protected:
		bool _is_enable = false;

		template<int index, class... Ts>
 		struct _print_tuple {
     		void operator() (std::tuple<Ts...>& t) {
         		_stream << get<index>(t) << " ";
         		_print_tuple<index - 1, Ts...>{}(t);
     		}
 		};

 		template<class... Ts>
 		struct _print_tuple<0, Ts...> {
     		void operator() (std::tuple<Ts...>& t) {
         		_stream << get<0>(t) << " ";
     		}
 		};

 		template<class... Ts>
 		void _print(std::tuple<Ts...>& t) {
   			const auto size = tuple_size<tuple<Ts...>>::value;
     		_print_tuple<size - 1, Ts...>{}(t);
 		}

	private:	
		std::ostream *_stream = NULL;
	}; // End Logger
*/
}; // End namespace

#endif // __cplusplus
#endif // _ACI_COMM_UAV_LOGGER_HPP_
