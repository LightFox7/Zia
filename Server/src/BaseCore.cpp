#include "BaseCore.hpp"

BaseCore::BaseCore(
    Modules::ptr    modules,
    uint16_t        port,
    bool            isHttps
)
:   _modules(modules),
    _socketsQueue(std::make_shared<SafeQueue<Socket::ptr>>()),
    _server(port, this->_socketsQueue)
{
    for (int i = 0; i < NB_INSTANCES; i++)
        this->_instances.emplace_back(isHttps);
}

void BaseCore::run()
{
    this->_server.listenAndServe();

    for (auto &inst : this->_instances)
        inst.run(_modules, this->_socketsQueue);
}