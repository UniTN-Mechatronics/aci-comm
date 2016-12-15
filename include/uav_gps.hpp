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
      latitude._update_read_type(uav_ptr);
      longitude._update_read_type(uav_ptr);
      height._update_read_type(uav_ptr);
      x_d._update_read_type(uav_ptr);
      y_d._update_read_type(uav_ptr);
      heading._update_read_type(uav_ptr);
      sat_num._update_read_type(uav_ptr);
      status._update_read_type(uav_ptr);
      time_of_week._update_read_type(uav_ptr);
      week._update_read_type(uav_ptr);

      accuracy.position._update_read_type(uav_ptr);
      accuracy.height._update_read_type(uav_ptr);
      accuracy.speed._update_read_type(uav_ptr);
    };

    template<class TP, class ReturnValue>
    class GPSLatLong : public ChannelRead<TP, ReturnValue>
    {
    public:
      friend class GPS;

      GPSLatLong() {};

    protected:
      void
      _update_read_type(TP *uav_ptr, Var read_type) {
        ChannelRead<TP, ReturnValue>::_uav_ptr   = uav_ptr
        ChannelRead<TP, ReturnValue>::_read_type = read_type
      }

      ReturnType
      _read_conversion(int value) {
          return gps_lat_long_read_conv(value);
      }
    };

    template<class TP, class ReturnValue>
    class GPSGeneralConvert : public ChannelRead<TP, ReturnValue>
    {
    public:
      friend class GPS;

      GPSGeneralConvert() {};

    protected:
      void
      _update_read_type(TP *uav_ptr, Var read_type) {
        ChannelRead<TP, ReturnValue>::_uav_ptr   = uav_ptr;
        ChannelRead<TP, ReturnValue>::_read_type = read_type;
      }

      ReturnType
      _read_conversion(int value) {
          return gps_general_read_conv(value);
      }
    };

    template<class TP, class ReturnValue>
    class GPSGeneral : public ChannelRead<TP, ReturnValue>
    {
    public:
      friend class GPS;

      GPSGeneral() {};

    protected:
      void
      _update_read_type(TP *uav_ptr, Var read_type) {
        ChannelRead<TP, ReturnValue>::_uav_ptr   = uav_ptr;
        ChannelRead<TP, ReturnValue>::_read_type = read_type;
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

    GPSGeneralConverts<T, FloatingPointPrecision> height;
    GPSGeneralConverts<T, FloatingPointPrecision> x_d;
    GPSGeneralConverts<T, FloatingPointPrecision> y_d;
    GPSGeneralConverts<T, FloatingPointPrecision> heading;
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
