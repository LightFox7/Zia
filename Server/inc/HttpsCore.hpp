#pragma once

#include "BaseCore.hpp"

#define DEFAULT_HTTPS_PORT 4343

class HttpsCore : public BaseCore
{
    public:
        HttpsCore(
            Modules::ptr modules,
            uint16_t    port = DEFAULT_HTTPS_PORT
        );
        ~HttpsCore() = default;
};