#ifndef _ACI_COMM_COMMONS_HPP_
#define _ACI_COMM_COMMONS_HPP_
#ifdef __cplusplus

namespace acc {

	enum class CTRL_MODE 
	{
		DIMC,
		DMC,
		CTRL,
		READ
	};
}

extern "C" {
    #include "asctecCommIntf.h"
}

#endif // __cplusplus
#endif // _ACI_COMM_COMMONS_HPP_







