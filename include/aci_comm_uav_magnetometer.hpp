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

#ifndef _ACI_COMM_MAGNETOMETER_HPP_
#define _ACI_COMM_MAGNETOMETER_HPP_
#ifdef __cplusplus

#include "aci_comm_engine.hpp"
#include "aci_comm_uav.hpp"
#include "aci_comm_misc_conversion_lambda.hpp"
#include "aci_comm_uav_commons.hpp"

namespace acc
{
  template<class T, class FloatingPointPrecision>
  class MagnetoMeter
  {

  private:

    MagnetoMeter(T *uav_ptr) {
      x.ChannelRead<T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
      y.ChannelRead<T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
      z.ChannelRead<T, FloatingPointPrecision>::_uav_ptr = uav_ptr;

      y.ChannelRead<T, FloatingPointPrecision>::_read_type = ACI_COMM_VAR::Hy;
      z.ChannelRead<T, FloatingPointPrecision>::_read_type = ACI_COMM_VAR::Hz;
    };

    template<class TP, class ReturnValue>
    class XMagnetoMeter: public virtual ChannelRead<TP, ReturnValue>
    {
    private:
      XMagnetoMeter() {
        ChannelRead<TP, ReturnValue>::_read_type = ACI_COMM_VAR::Hx;
      };

    protected:
      ReturnValue _read_conversion(int value) {
        return h_read_conv(value);
      }

    public:
      friend class MagnetoMeter;
    }; /* class XMagnetoMeter */

    template<class TP, class ReturnValue>
    class YZMagnetoMeter: public virtual ChannelRead<TP, ReturnValue>
    {
    private:
      YZMagnetoMeter() {
        // ChannelRead<T, FloatingPointPrecision>::_read_type = H_y;
      };

    protected:
      ReturnValue _read_conversion(int value) {
        return h_read_conv(value) *
          static_cast<ReturnValue>(ChannelRead<TP, ReturnValue>::_uav_ptr->orientation); // TODO: Check this
      }

    public:
      friend class MagnetoMeter;
    }; /* class YZMagnetoMeter */

  public:
    friend class UAV;
    XMagnetoMeter<T, FloatingPointPrecision>  x;
    YZMagnetoMeter<T, FloatingPointPrecision> y;
    YZMagnetoMeter<T, FloatingPointPrecision> z;

    MagnetoMeter() {};

  }; /* classMagnetoMeter */

} /* namspace acc */

#endif /* ifdef __cplusplus */
#endif /* define _ACI_COMM_MAGNETOMETER_HPP_ */
