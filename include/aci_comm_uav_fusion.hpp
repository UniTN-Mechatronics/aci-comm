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

#ifndef _ACI_COMM_UAV_FUSION_HPP_
#define _ACI_COMM_UAV_FUSION_HPP_
#ifdef __cplusplus

#include "aci_comm_engine.hpp"
#include "aci_comm_uav.hpp"
#include "aci_comm_misc_conversion_lambda.hpp"
#include "aci_comm_uav_commons.hpp"

namespace acc
{
  template<class T, class FloatingPointPrecision>
  class Fusion
  {

  private:

    Fusion(T* uav_ptr) {
      latitude._update_read_type(uav_ptr, Var::fusion_latitude, fusion_lat_long_read_conv);
      longitude._update_read_type(uav_ptr, Var::fusion_longitude, fusion_lat_long_read_conv);
      height_d._update_read_type(uav_ptr, Var::fusion_dheight, fusion_h_dh_read_conv);
      height._update_read_type(uav_ptr, Var::fusion_height, fusion_h_dh_read_conv);
      u_d._update_read_type(uav_ptr, Var::fusion_speed_x, fusion_speed_read_conv);
      v_d._update_read_type(uav_ptr, Var::fusion_speed_y, fusion_speed_read_conv);
    };

    template<class TP, class ReturnType>
    class FusionElement : public ChannelRead<TP, ReturnType>
    {
    public:
      friend class Fusion;

      FusionElement() {};

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

    FusionElement<T, FloatingPointPrecision> latitude;
    FusionElement<T, FloatingPointPrecision> longitude;
    FusionElement<T, FloatingPointPrecision> height_d;
    FusionElement<T, FloatingPointPrecision> height;
    FusionElement<T, FloatingPointPrecision> u_d;
    FusionElement<T, FloatingPointPrecision> v_d;

    Fusion() {};

  }; /* class Fusion */

} /* namspace acc */

#endif /* ifdef __cplusplus */
#endif /* define _ACI_COMM_UAV_FUSION_HPP_ */
