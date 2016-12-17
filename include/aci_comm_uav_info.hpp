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

#ifndef _ACI_COMM_UAV_INFO_HPP_
#define _ACI_COMM_UAV_INFO_HPP_
#ifdef __cplusplus

#include <functional>

#include "aci_comm_engine.hpp"
#include "aci_comm_uav.hpp"
#include "aci_comm_misc_conversion_lambda.hpp"
#include "aci_comm_uav_commons.hpp"

namespace acc
{
  template<class T, class FloatingPointPrecision>
  class Infos
  {

  private:

    Infos(T* uav_ptr) {
      status._update_read_type(uav_ptr, Var::UAV_status, [](int v) -> int { return v; });
      flight_time._update_read_type(uav_ptr, Var::flight_time, flight_time_read_conv);
      battery_voltage._update_read_type(uav_ptr, Var::battery_voltage, battery_voltage_read_conv);
      cpu_load._update_read_type(uav_ptr, Var::HL_cpu_load, hl_cpu_load_read_conv);
      up_time._update_read_type(uav_ptr, Var::HL_up_time, hl_up_time_read_conv);
    };

    template<class TP, class ReturnType>
    class InfoElement : public ChannelRead<TP, ReturnType>
    {
    public:
      friend class Infos;

      InfoElement() {};

    protected:

      void
      _update_read_type(TP *uav_ptr, Var read_type, std::function<ReturnType(int)> conv_func) {
        ChannelRead<TP, ReturnType>::_uav_ptr   = uav_ptr;
        ChannelRead<TP, ReturnType>::_read_type = read_type;
        _conv_func                              = conv_func;
      }

      ReturnType
      _read_conversion(int value) {
          return _conv_func(value);
      }

    private:
      std::function<ReturnType(int)> _conv_func;
    };

  public:
    friend class UAV;
    InfoElement<T, int> status;
    InfoElement<T, int> flight_time;
    InfoElement<T, FloatingPointPrecision> battery_voltage;
    InfoElement<T, int> cpu_load;
    InfoElement<T, FloatingPointPrecision> up_time;

    Infos() {};

  }; /* class Infos */

} /* namspace acc */
/*
UAV_status             = 0, //
flight_time            ,    //
battery_voltage        ,    //
HL_cpu_load            ,    //
HL_up_time             ,    //
*/
#endif /* ifdef __cplusplus */
#endif /* define _ACI_COMM_UAV_INFOS_HPP_ */
