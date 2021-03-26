#pragma once

#include "Server.hpp"
#include "Modules.hpp"
#include "ClientsInstance.hpp"

#define NB_INSTANCES 3

class BaseCore
{
    public:
        BaseCore(
            Modules::ptr    modules,
            uint16_t        port,
            bool            isHttps
        );
        ~BaseCore() = default;

        void run();

    private:
        Modules::ptr _modules;
        Server::SocketsQueue _socketsQueue;
        Server _server;
        std::vector<ClientsInstance> _instances;
};