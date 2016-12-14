#ifndef _ACI_COMM_UAV_MOTORS_HPP_
#define _ACI_COMM_UAV_MOTORS_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "aci_comm_uav.hpp"
#include "conversion_lambda.hpp"
#include "uav_commons.hpp"

namespace acc
{
    template<class T, class FloatingPointPrecision>
    class Motor: public virtual ChannelRead<T, int>, public virtual ChannelWrite<T, FloatingPointPrecision>
    {
    private:

        Motor(T *uav_ptr, ACI_COMM_VAR aci_comm_var, ACI_COMM_CMD aci_comm_cmd) {
            ChannelRead<T, int>::_uav_ptr = uav_ptr;
            ChannelWrite<T, FloatingPointPrecision>::_uav_ptr = uav_ptr;
            ChannelRead<T, int>::_read_type = aci_comm_var;
            ChannelWrite<T, FloatingPointPrecision>::_write_type = aci_comm_cmd;
        };

    protected:
        int
        _read_conversion(int value) {
            return motor_rpm_read_conv(value);
        }

        int
        _write_conversion(FloatingPointPrecision value) {
            return DIMC_motor_write_conv(value);
        }

        void 
        _ctrl_mode_check() {
            if (ChannelWrite<T, FloatingPointPrecision>::_uav_ptr->_ctrl_mode == CTRL_MODE::DIMC) return;
            throw std::runtime_error("Motors can be controlled only with control mode set to DIMC");
        }

    public:
        friend class UAV;
        Motor() {};

    };

}; // end namespace


#endif // __cplusplus
#endif // _ACI_COMM_UAV_MOTORS_HPP_
