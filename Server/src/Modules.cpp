#include "Modules.hpp"

Modules::Modules()
{
    _connectionWrapper = nullptr;
    _parser = nullptr;
    _isExit = false;
}

Modules::ptr Modules::create()
{
    return std::make_unique<Modules>();
}