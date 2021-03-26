#include "HttpsCore.hpp"

HttpsCore::HttpsCore(
    Modules::ptr modules,
    uint16_t    port
)
:   BaseCore(modules, port, true) {}