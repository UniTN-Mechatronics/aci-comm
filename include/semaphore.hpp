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

#ifndef _SEMAPHORE_HPP_
#define _SEMAPHORE_HPP_
#ifdef __cplusplus

class Semaphore
{
public:
    Semaphore(int value) : _value(value) {};
    Semaphore(const Semaphore &S) = delete;
    Semaphore& operator=(Semaphore S) = delete;
    ~Semaphore() {};

    void
    wait() {
        std::unique_lock<std::mutex> lock(_mutex);
        --_value;
        if (_value < 0) {
            do {
                _cv.wait(lock);
            } while (_wake_ups < 1);
            --_wake_ups;
        }
    }

    void 
    signal() {
        std::unique_lock<std::mutex> lock(_mutex);
        ++_value;
        if (_value <= 0) {
            ++_wake_ups;
            _cv.notify_one();
        }
    }

private:
    int _value;
    int _wake_ups = 0;
    std::mutex _mutex;
    std::condition_variable _cv;
};


#endif // __cplusplus
#endif // _ACI_COMM_SEMAPHORE_HPP_
