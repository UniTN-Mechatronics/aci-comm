#ifndef _ACI_COMM_UAV_FRAME_HPP_
#define _ACI_COMM_UAV_FRAME_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "aci_comm_uav.hpp"

#define ENABLE_READ()                                               \
enable_read(int packet) {                                           \
    _check_null_uav_ptr(_uav_ptr);                                  \
    _uav_ptr->engine->add_read(packet, read_type);                  \
    return *this;                                                   \
} 

#define ENABLE_WRITE()                                              \
enable_write(int packet) {                                          \
    _check_null_uav_ptr(_uav_ptr);                                  \
    _uav_ptr->engine->add_write(packet, write_type);                \
    return *this;                                                   \
} 

#define READ()                                                      \
read() {                                                            \
    _check_null_uav_ptr(_uav_ptr);                                  \
    return _read_conversion(_uav_ptr->engine->read(read_type));     \
}

#define WRITE()                                                     \
write(double val) {                                                 \
    _check_null_uav_ptr(_uav_ptr);                                  \
    auto val_conv = _write_conversion(val);                         \
    _uav_ptr->engine->write(val_conv, val);                         \
    return *this;                                                   \
}

#define PROTECTED_ITEM()                                            \
TP *_uav_ptr = NULL;                                                \
void                                                                \
_check_null_uav_ptr(TP *uav_ptr) noexcept(false) {                  \
    if (!uav_ptr) throw std::runtime_error("UAV pointer is null!"); \
}    

namespace acc 
{
    template<class T>
    class Angles 
    {
    private:

        Angles(T *uav_ptr) {
            yaw._uav_ptr   = uav_ptr;
            pitch._uav_ptr = uav_ptr;
            roll._uav_ptr  = uav_ptr;
        };
    
        /*
        *    __          
        *   |__).|_ _|_  
        *   |   ||_(_| ) 
        */
        template<class TP>
        class Pitch 
        {
        public:
            friend class Angles;
            Pitch& ENABLE_READ()
            Pitch& ENABLE_WRITE()
            double READ()
            Pitch& WRITE()
            
        protected:
            ACI_COMM_VAR read_type  = ACI_COMM_VAR::angle_pitch;
            ACI_COMM_CMD write_type = ACI_COMM_CMD::CTRL_pitch;
            PROTECTED_ITEM()

            double 
            _read_conversion(int value) {
                return (double)value;
            }

            int 
            _write_conversion(double value) {
                return (int)value;
            }
        };


        /*
        *    __      
        *   |__)_ || 
        *   | \(_)|| 
        */
        template<class TP>
        class Roll 
        {
        public:
            friend class Angles;
            Roll& ENABLE_READ()
            Roll& ENABLE_WRITE()
            double READ()
            Roll& WRITE()
            
        protected:
            ACI_COMM_VAR read_type  = ACI_COMM_VAR::angle_roll;
            ACI_COMM_CMD write_type = ACI_COMM_CMD::CTRL_roll;
            PROTECTED_ITEM()

            double 
            _read_conversion(int value) {
                return (double)value;
            }

            int 
            _write_conversion(double value) {
                return (int)value;
            }
        };


        /*
        *   \_/_     
        *    |(_|\)/ 
        */
        template<class TP>
        class Yaw 
        {
        public:
            friend class Angles;
            Yaw& ENABLE_READ()
            double READ()
            
        protected:
            ACI_COMM_VAR read_type  = ACI_COMM_VAR::angle_yaw;
            PROTECTED_ITEM()

            double 
            _read_conversion(int value) {
                return (double)value;
            }
        };

    public:
        friend class UAV;
        Yaw<T> yaw;
        Pitch<T> pitch;
        Roll<T> roll;
        Angles() {};
    };

};

#endif // __cplusplus
#endif // _ACI_COMM_UAV_FRAME_HPP_

