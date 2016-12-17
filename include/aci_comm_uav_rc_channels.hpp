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

#ifndef _ACI_COMM_UAV_RC_CHANNELS_HPP_
#define _ACI_COMM_UAV_RC_CHANNELS_HPP_
#ifdef __cplusplus

#include "aci_comm_engine.hpp"
#include "aci_comm_uav.hpp"
#include "aci_comm_misc_conversion_lambda.hpp"
#include "aci_comm_uav_commons.hpp"

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
