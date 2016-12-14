#ifndef _ACI_COMM_UAV_RC_CHANNELS_HPP_
#define _ACI_COMM_UAV_RC_CHANNELS_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "aci_comm_uav.hpp"
#include "conversion_lambda.hpp"
#include "uav_commons.hpp"

namespace acc
{
  template<class T, class FloatingPointPrecision>
  class RCChannel: public virtual ChannelRead<T, FloatingPointPrecision>
  {
  private:
    RCChannel(T *uav_ptr, ACI_COMM_VAR aci_comm_var) {
      ChannelRead<T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
      ChannelRead<T, FloatingPointPrecision>::_read_type = aci_comm_var;
    };

  protected:
    FloatingPointPrecision _read_conversion(int value) {
      return rc_channel_read_conv(value);
    }

  public:
    friend class UAV;
    RCChannel() {};
  }; /* class RCChannel */
} /* namspace acc */

#endif /* ifdef __cplusplus */
#endif /* define _ACI_COMM_UAV_RC_CHANNELS_HPP_ */
