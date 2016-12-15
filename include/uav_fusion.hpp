#ifndef _ACI_COMM_UAV_FUSION_HPP_
#define _ACI_COMM_UAV_FUSION_HPP_
#ifdef __cplusplus

#include "engine.hpp"
#include "aci_comm_uav.hpp"
#include "conversion_lambda.hpp"
#include "uav_commons.hpp"

namespace acc
{
  template<class T, class FloatingPointPrecision>
  class Fusion
  {

  private:

    Fusion(T* uav_ptr) {

    };

  public:
    friend class UAV;

    Fusion() {};

  }; /* class Fusion */

} /* namspace acc */

#endif /* ifdef __cplusplus */
#endif /* define _ACI_COMM_UAV_FUSION_HPP_ */
