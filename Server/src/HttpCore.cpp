#include <iostream>

#include "HttpCore.hpp"

HttpCore::HttpCore(
    Modules::ptr modules,
    uint16_t    port
)
:   BaseCore(modules, port, false) {}