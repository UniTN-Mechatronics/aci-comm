#ifndef _ACI_COMM_UAV_COMMONS_HPP_
#define _ACI_COMM_UAV_COMMONS_HPP_
#ifdef __cplusplus

namespace acc 
{
        
};
/*
#define ENABLE_READ()                                               \
enable_read(int packet) {                                           \
    _check_null_uav_ptr(_uav_ptr);                                  \
    _uav_ptr->engine->add_read(packet, _read_type);                 \
    return *this;                                                   \
} 

#define ENABLE_WRITE()                                              \
enable_write(int packet) {                                          \
    _check_null_uav_ptr(_uav_ptr);                                  \
    _ctrl_mode_check();                                             \
    _uav_ptr->engine->add_write(packet, _write_type);               \
    return *this;                                                   \
} 

#define READ()                                                      \
read() {                                                            \
    _check_null_uav_ptr(_uav_ptr);                                  \
    return _read_conversion(_uav_ptr->engine->read(_read_type));    \
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

#define READ_TYPE()                                                 \
ACI_COMM_VAR                                                        \
read_type() {                                                       \
    return _read_type;                                              \
}

#define WRITE_TYPE()                                                \
ACI_COMM_CMD                                                        \
write_type() {                                                      \
    return _write_type;                                             \
}
*/
#endif // __cplusplus
#endif // _ACI_COMM_UAV_COMMONS_HPP_
