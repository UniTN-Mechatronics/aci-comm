#ifndef _ACI_COMM_MAGNETOMETER_HPP_
#define _ACI_COMM_MAGNETOMETER_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "aci_comm_uav.hpp"
#include "conversion_lambda.hpp"
#include "uav_commons.hpp"

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
