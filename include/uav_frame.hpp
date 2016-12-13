#ifndef _ACI_COMM_UAV_FRAME_HPP_
#define _ACI_COMM_UAV_FRAME_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "aci_comm_uav.hpp"

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
            
            Pitch&
            enable_read(int packet) {
                _check_null_uav_ptr(_uav_ptr);
                _uav_ptr->engine->add_read(packet, ACI_COMM_VAR::angle_pitch);
                return *this;
            }

            Pitch& 
            enable_write(int packet) {
                _check_null_uav_ptr(_uav_ptr);
                _uav_ptr->engine->add_write(packet, ACI_COMM_CMD::CTRL_pitch);
                return *this;
            }

            double 
            read() { 
                _check_null_uav_ptr(_uav_ptr);
                return _uav_ptr->engine->read(ACI_COMM_VAR::angle_pitch);
            }

            Pitch& 
            write(double val) {
                _check_null_uav_ptr(_uav_ptr);
                _uav_ptr->engine->write(ACI_COMM_CMD::CTRL_pitch, val);
                return *this;
            }

        protected:
            TP *_uav_ptr = NULL;    
            
            void 
            _check_null_uav_ptr(TP *uav_ptr) noexcept(false) {
                if (!uav_ptr) throw std::runtime_error("UAV pointer is null!");
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

            void 
            enable_read(int packet) {
                _uav_ptr->engine->add_read(packet, ACI_COMM_VAR::angle_roll);
            }

            void 
            enable_write(int packet) {
                _uav_ptr->engine->add_write(packet, ACI_COMM_CMD::CTRL_roll);
            }

            double 
            read() { 
                return _uav_ptr->engine->read(ACI_COMM_VAR::angle_roll);
            }

            void 
            write(double val) {
                _uav_ptr->engine->write(ACI_COMM_CMD::CTRL_roll, val);
            }

        protected:
            TP *_uav_ptr = NULL;
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

            void 
            enable_read(int packet) {
                _uav_ptr->engine->add_read(packet, ACI_COMM_VAR::angle_yaw);
            }

            double 
            read() { 
                return _uav_ptr->engine->read(ACI_COMM_VAR::angle_yaw);
            }

        protected:
            TP *_uav_ptr = NULL;
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

