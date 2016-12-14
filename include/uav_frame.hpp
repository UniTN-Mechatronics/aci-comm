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
            
        protected:
            ACI_COMM_VAR read_type  = ACI_COMM_VAR::angle_pitch;
            ACI_COMM_CMD write_type = ACI_COMM_CMD::CTRL_pitch;
            PROTECTED_ITEM()

            double 
            _read_conversion(int value) {
                return angle_read_conv(value);
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
                return angle_read_conv(value);
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

