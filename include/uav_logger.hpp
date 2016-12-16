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

#ifndef _ACI_COMM_UAV_LOGGER_HPP_
#define _ACI_COMM_UAV_LOGGER_HPP_
#ifdef __cplusplus

#include <fstream>
#include <iostream>
#include <ostream>
#include <utility>
#include <iomanip>
#include <mutex>
#include <chrono>
#include "aci_comm_uav.hpp"

namespace acc 
{
	class Timer
	{
	public:
		Timer() {};
		virtual ~Timer() {};

	private:
		std::chrono::high_resolution_clock::time_point _start_time;

	};

	class Logger
	{	
	public:	
		using CharType = std::string;
		CharType separator  = "\t";
		CharType start_line = "";
		CharType end_line 	= "\n";
		int floating_point_digits = 3;
		
		Logger(std::ostream& stream) : _stream(stream), _mutex() {
			_start_time = _set_start_time();
		}
		virtual ~Logger() {};
	
		template<class T, class... Args> Logger& 
		log(T t, Args... args) {
			//std::unique_lock<std::mutex> lock(_mutex);
			const int n = sizeof...(Args);
			_args_size = n + 1;
			_args_size_init = _args_size;
			_print(t);
			_print(args...);
			return *this;
		}
	
		template<class T> Logger&
		log(T val) {
			//std::unique_lock<std::mutex> lock(_mutex);
			_stream << start_line << val << end_line;	
			return *this;
		}

		Logger&
		reset_start_time() {
			//std::unique_lock<std::mutex> lock(_mutex);
			_start_time = _set_start_time();
			return *this;
		}

		double 
		time() {
			//std::unique_lock<std::mutex> lock(_mutex);
			return (_time_since(_start_time) / 1000.0f);
		}

		int 
		time_ms() {
			//std::unique_lock<std::mutex> lock(_mutex);
			return static_cast<int>(_time_since(_start_time));
		}

	private:
		//std::vector<std::ostream> &_streams; 
		std::ostream &_stream;
		int _args_size = 0;
		int _args_size_init = 0;
		std::mutex _mutex;
		std::chrono::high_resolution_clock::time_point _start_time;

		template<class T, class... Args> void
		_print(T t, Args... args) {
			_print(t);
			_print(args...);
		}
	
		template<class T> void
		_print(T val) {
			--_args_size;
			if (_args_size == 0) {
				_stream << std::fixed << std::setprecision(floating_point_digits) << val << end_line;	
			} else if ((_args_size + 1) == (_args_size_init)) {
				_stream << std::fixed << std::setprecision(floating_point_digits) << start_line << val << separator;	
			} else {
				_stream << std::fixed << std::setprecision(floating_point_digits) << val << separator;
			}
		}

    	std::chrono::high_resolution_clock::time_point 
    	_set_start_time() {
    		return std::chrono::high_resolution_clock::now();
    	}

    	double 
    	_time_since(std::chrono::high_resolution_clock::time_point t1) {
    	  	auto t2 = std::chrono::high_resolution_clock::now();
    	  	auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    	  	return time_span.count();
    	}

	}; // End Logger
}; // End namespace

#endif // __cplusplus
#endif // _ACI_COMM_UAV_LOGGER_HPP_
