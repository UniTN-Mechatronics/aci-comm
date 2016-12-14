#ifndef _ACI_COMM_UAV_COMMONS_HPP_
#define _ACI_COMM_UAV_COMMONS_HPP_
#ifdef __cplusplus

#include "aci_comm_uav.hpp"
#include "conversion_lambda.hpp"

#ifndef MOTORS_NUM
#define MOTORS_NUM 4
#endif

#ifndef RC_CHANNELS_NUM
#define RC_CHANNELS_NUM 8
#endif

#ifndef FLOATING_POINT_PRECISION
#define FLOATING_POINT_PRECISION double
#endif

namespace acc
{
    template<class TP>
    class Channel
    {
    public:
        virtual ~Channel() {};

    protected:
        TP *_uav_ptr = NULL;
        void
        _check_null_uav_ptr(TP *uav_ptr) noexcept(false) {
            if (!uav_ptr) throw std::runtime_error("UAV pointer is null!");
        }
    };

    template<class TP, class ReturnType>
    class ChannelRead: public Channel<TP>
    {
    public:
        virtual ~ChannelRead() {};

        virtual ChannelRead&
        enable_read(int packet) {
            Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);
            Channel<TP>::_uav_ptr->engine->add_read(packet, _read_type);
            return *this;
        }

        virtual ReturnType
        read() {
            Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);
            return _read_conversion(Channel<TP>::_uav_ptr->engine->read(_read_type));
        }

        ACI_COMM_VAR
        get_read_id() {
            return _read_type;
        }

    protected:
        virtual ReturnType
        _read_conversion(int value) {
            return (ReturnType)value;
        }

        ACI_COMM_VAR _read_type;
    };

    template<class TP, class ArgType>
    class ChannelWrite: public Channel<TP>
    {
    public:
        virtual ~ChannelWrite() {};

        virtual ChannelWrite&
        enable_write(int packet) {
            Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);
            _ctrl_mode_check();
            Channel<TP>::_uav_ptr->engine->add_write(packet, _write_type);
            return *this;
        }

        virtual ChannelWrite&
        write(ArgType val) {
            Channel<TP>::_check_null_uav_ptr(Channel<TP>::_uav_ptr);
            auto val_conv = _write_conversion(val);
            Channel<TP>::_uav_ptr->engine->write(_write_type, val_conv);
            return *this;
        }

        ACI_COMM_CMD
        get_write_id() {
            return _write_type;
        }

    protected:
        ACI_COMM_CMD _write_type;

        virtual int
        _write_conversion(ArgType value) {
            return (int)value;
        }

        virtual void
        _ctrl_mode_check() {
            if (Channel<TP>::_uav_ptr->_ctrl_mode == CTRL_MODE::DMC || Channel<TP>::_uav_ptr->_ctrl_mode == CTRL_MODE::CTRL) return;
            throw std::runtime_error("Pitch can be written only with control mode setted to DMC or CTRL");
        }
    };

};

#endif // __cplusplus
#endif // _ACI_COMM_UAV_COMMONS_HPP_
