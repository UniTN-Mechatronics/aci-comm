#ifndef _ACI_COMM_UAV_INFO_HPP_
#define _ACI_COMM_UAV_INFO_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "aci_comm_uav.hpp"
#include "conversion_lambda.hpp"
#include "uav_commons.hpp"

namespace acc
{
  template<class T, class FloatingPointPrecision>
  class Infos
  {

  private:

    Infos(T* uav_ptr) {

    };

  public:
    friend class UAV;

    Infos() {};

  }; /* class Infos */

} /* namspace acc */

#endif /* ifdef __cplusplus */
#endif /* define _ACI_COMM_UAV_INFOS_HPP_ */
