#ifndef _ACC_EXPLICITS_TEMPLATES_HPP_
#define _ACC_EXPLICITS_TEMPLATES_HPP_
#ifdef __cplusplus

/**
*	Include this file at the end of 
*	the *engine.cpp* file.
*
*   Explicit template instantiation.
*   Needed in order to keep the Engine
*   implementation in the .cpp file,
*   so we can use the anonymous namespace
*   in the .cpp.
*/
template class acc::Engine<acc::SerialBus>;


/** 
*	So if we will develop an acc::I2CBus, we 
*	will need to uncomment the following:
*/
// template class acc::Engine<acc::I2CBus>;


#endif // __cplusplus
#endif // _ACC_EXPLICITS_TEMPLATES_HPP_
