#pragma once

#include "BaseCore.hpp"

#define DEFAULT_HTTP_PORT 8080

class HttpCore : public BaseCore
{
    public:
        HttpCore(
            Modules::ptr modules,
            uint16_t    port = DEFAULT_HTTP_PORT
        );
        ~HttpCore() = default;
};