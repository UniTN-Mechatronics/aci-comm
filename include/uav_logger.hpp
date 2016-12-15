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
