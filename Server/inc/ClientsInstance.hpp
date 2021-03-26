#pragma once

#include <thread>
#include <list>

#include "Client.hpp"
#include "Server.hpp"
#include "Modules.hpp"
#include "Loggers.hpp"

#define MAX_CLIENT 100

// Need to takes modules
class ClientsInstance
{
    public:
        ClientsInstance() = delete;
        ClientsInstance(const ClientsInstance &) = delete;

        // Required for vector.emplace_back()
        ClientsInstance(ClientsInstance &&) = default;
        ClientsInstance(bool useConnectionWrapper);
        ~ClientsInstance();

        void run(Modules::ptr modules, const Server::SocketsQueue &sockQueue);

    private:
        class Instance
        {
            public:
                void run(
                    Modules::ptr                modules,
                    bool                        useConnectionWrapper,
                    const Server::SocketsQueue  &sockQueue
                );

            private:
                Modules::ptr _modules;
                bool _useConnectionWrapper;

                void handleNewClient(
                    const Server::SocketsQueue  &sockQueue,
                    std::vector<Client::ptr>    &clients,
                    bool useConnectionWrapper
                );
                void clientsLoop(std::vector<Client::ptr> &clients);
        };

    private:
        bool _useConnectionWrapper;
        bool _running;
        Modules::ptr _modules;
        std::thread _thread;
};