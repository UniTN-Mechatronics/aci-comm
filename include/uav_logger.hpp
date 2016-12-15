#ifndef _ACI_COMM_UAV_LOGGER_HPP_
#define _ACI_COMM_UAV_LOGGER_HPP_
#ifdef __cplusplus

#include <fstream>
#include <iostream>
#include <ostream>
#include <tuple>
#include "aci_comm_uav.hpp"

namespace acc 
{
	class Logger
	{
	private:
		using CharType = std::string;
	
	public:	
		CharType separator  = "\t";
		CharType start_line = "(";
		CharType end_line 	= ")\n";
		
		Logger(std::ostream& stream_) : stream(stream_) {}
	
		template<class T, class... Args>
		void print(T t, Args... args) {
			print(t);
			print(args...);
		}
	
		template<class T> void
		print(T val) {
			stream << val << " ";
		}
	
		std::ostream &stream;
	};
}; // End namespace

#endif // __cplusplus
#endif // _ACI_COMM_UAV_LOGGER_HPP_
