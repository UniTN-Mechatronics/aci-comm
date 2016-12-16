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

    template<class T>
    class DroneItem
    {
    public:
        DroneItem(T id, 
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

        T
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
        T _id;
        int _num_id;
        DIP _rw;
        int _value;
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
