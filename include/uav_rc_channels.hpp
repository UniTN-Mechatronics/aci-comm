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
      template<class K, class KK> friend class RCChannelCollection;
      RCChannel() {};
    }; /* class RCChannel */


    template<class T, class FloatingPointPrecision>
    class RCChannelCollection {
    private:
        using RCChannel_ = RCChannel<T, FLOATING_POINT_PRECISION>;
        int _number_of_channels = RC_CHANNELS_NUM;
        std::vector<RCChannel<T, FloatingPointPrecision>> _channels;

        RCChannelCollection(T *uav_ptr) {
            _channels.push_back(RCChannel_(uav_ptr, ACI_COMM_VAR::RC_channel_0));
            _channels.push_back(RCChannel_(uav_ptr, ACI_COMM_VAR::RC_channel_1));
            _channels.push_back(RCChannel_(uav_ptr, ACI_COMM_VAR::RC_channel_2));
            _channels.push_back(RCChannel_(uav_ptr, ACI_COMM_VAR::RC_channel_3));
            _channels.push_back(RCChannel_(uav_ptr, ACI_COMM_VAR::RC_channel_4));
            _channels.push_back(RCChannel_(uav_ptr, ACI_COMM_VAR::RC_channel_5));
            _channels.push_back(RCChannel_(uav_ptr, ACI_COMM_VAR::RC_channel_6));
            _channels.push_back(RCChannel_(uav_ptr, ACI_COMM_VAR::RC_channel_7));
        };

    public:
        friend class UAV;
        RCChannelCollection() {};

        RCChannel_
        operator[](int index) {
            if (index < 0 || index > (_number_of_channels - 1)) {
                std::runtime_error("RCChannelCollection index is or greater than number of motors or less than zero");
            }
            return _channels[index];
        }

        RCChannelCollection&
        enable_read(int packet) {
            for (auto &m : _channels) m.enable_read(packet);
            return *this;
        }

        std::vector<FloatingPointPrecision>
        read() {
            std::vector<FloatingPointPrecision> read_m;
            for (auto &m : _channels) {
                read_m.push_back(m.read());
            }
            return read_m;
        }

    }; // End RCChannelCollection

} /* namspace acc */

#endif /* ifdef __cplusplus */
#endif /* define _ACI_COMM_UAV_RC_CHANNELS_HPP_ */
