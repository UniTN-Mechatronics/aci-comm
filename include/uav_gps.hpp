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

#ifndef _ACI_COMM_UAV_GPS_HPP_
#define _ACI_COMM_UAV_GPS_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "aci_comm_uav.hpp"
#include "conversion_lambda.hpp"
#include "uav_commons.hpp"

namespace acc
{
  template<class T, class FloatingPointPrecision>
  class GPSS
  {

  private:

    GPSS(T* uav_ptr) {
      latitude._update_read_type(uav_ptr, Var::GPS_latitude);
      longitude._update_read_type(uav_ptr, Var::GPS_longitude);
      height._update_read_type(uav_ptr, Var::GPS_height);
      u_d._update_read_type(uav_ptr, Var::GPS_speed_x);
      v_d._update_read_type(uav_ptr, Var::GPS_speed_y);
      heading._update_read_type(uav_ptr, Var::GPS_heading);
      sat_num._update_read_type(uav_ptr, Var::GPS_sat_num);
      status._update_read_type(uav_ptr, Var::GPS_status);
      time_of_week._update_read_type(uav_ptr, Var::GPS_time_of_week);
      week._update_read_type(uav_ptr, Var::GPS_week);

      accuracy.position._update_read_type(uav_ptr, Var::GPS_position_accuracy);
      accuracy.height._update_read_type(uav_ptr, Var::GPS_height_accuracy);
      accuracy.speed._update_read_type(uav_ptr, Var::GPS_speed_accuracy);
    };

    template<class TP, class ReturnType>
    class GPSLatLong : public ChannelRead<TP, ReturnType>
    {
    public:
      friend class GPSS;

      GPSLatLong() {};

    protected:
      void
      _update_read_type(TP *uav_ptr, Var read_type) {
        ChannelRead<TP, ReturnType>::_uav_ptr   = uav_ptr;
        ChannelRead<TP, ReturnType>::_read_type = read_type;
      }

      ReturnType
      _read_conversion(int value) {
          return gps_lat_long_read_conv(value);
      }
    };

    template<class TP, class ReturnType>
    class GPSGeneralConvert : public ChannelRead<TP, ReturnType>
    {
    public:
      friend class GPSS;

      GPSGeneralConvert() {};

    protected:
      void
      _update_read_type(TP *uav_ptr, Var read_type) {
        ChannelRead<TP, ReturnType>::_uav_ptr   = uav_ptr;
        ChannelRead<TP, ReturnType>::_read_type = read_type;
      }

      ReturnType
      _read_conversion(int value) {
          return gps_general_read_conv(value);
      }
    };

    template<class TP, class ReturnType>
    class GPSGeneral : public ChannelRead<TP, ReturnType>
    {
    public:
      friend class GPSS;

      GPSGeneral() {};

    protected:
      void
      _update_read_type(TP *uav_ptr, Var read_type) {
        ChannelRead<TP, ReturnType>::_uav_ptr   = uav_ptr;
        ChannelRead<TP, ReturnType>::_read_type = read_type;
      }

      ReturnType
      _read_conversion(int value) {
          return value;
      }
    };

  public:
    friend class UAV;

    GPSLatLong<T, FloatingPointPrecision> latitude;
    GPSLatLong<T, FloatingPointPrecision> longitude;

    GPSGeneralConvert<T, FloatingPointPrecision> height;
    GPSGeneralConvert<T, FloatingPointPrecision> u_d;
    GPSGeneralConvert<T, FloatingPointPrecision> v_d;
    GPSGeneralConvert<T, FloatingPointPrecision> heading;
    class Accuracy {
    public:
      GPSGeneralConvert<T, FloatingPointPrecision> position;
      GPSGeneralConvert<T, FloatingPointPrecision> height;
      GPSGeneralConvert<T, FloatingPointPrecision> speed;
    };
    Accuracy accuracy;
    GPSGeneral<T, int> sat_num;
    GPSGeneral<T, int> status;
    GPSGeneralConvert<T, FloatingPointPrecision> time_of_week;
    GPSGeneral<T, int> week;

    GPSS() {};

  }; /* class GPSS */

} /* namspace acc */

#endif /* ifdef __cplusplus */
#endif /* define _ACI_COMM_UAV_GPS_HPP_ */
