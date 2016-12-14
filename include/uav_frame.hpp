#ifndef _ACI_COMM_UAV_FRAME_HPP_
#define _ACI_COMM_UAV_FRAME_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "aci_comm_uav.hpp"
#include "conversion_lambda.hpp"

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

            READ_TYPE()
            WRITE_TYPE()
            
        protected:
            ACI_COMM_VAR _read_type  = ACI_COMM_VAR::angle_pitch;
            ACI_COMM_CMD _write_type = ACI_COMM_CMD::CTRL_pitch;
            PROTECTED_ITEM()

            double 
            _read_conversion(int value) {
                return angle_read_conv(value);
            }

            int 
            _write_conversion(double value) {
                return (int)value;
            }

            void
            _ctrl_mode_check() {
                if (_uav_ptr->_ctrl_mode == CTRL_MODE::DMC || _uav_ptr->_ctrl_mode == CTRL_MODE::CTRL) return;
                throw std::runtime_error("Pitch can be written only with control mode setted to DMC or CTRL");
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

            READ_TYPE()
            WRITE_TYPE()
            
        protected:
            ACI_COMM_VAR _read_type  = ACI_COMM_VAR::angle_roll;
            ACI_COMM_CMD _write_type = ACI_COMM_CMD::CTRL_roll;
            PROTECTED_ITEM()

            double 
            _read_conversion(int value) {
                return angle_read_conv(value);
            }

            int 
            _write_conversion(double value) {
                return (int)value;
            }

            void
            _ctrl_mode_check() {
                if (_uav_ptr->_ctrl_mode == CTRL_MODE::DMC || _uav_ptr->_ctrl_mode == CTRL_MODE::CTRL) return;
                throw std::runtime_error("Roll can be written only with control mode setted to DMC or CTRL");
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

            READ_TYPE()
            
        protected:
            ACI_COMM_VAR _read_type  = ACI_COMM_VAR::angle_yaw;
            PROTECTED_ITEM()

            double 
            _read_conversion(int value) {
                return angle_read_conv(value);
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

