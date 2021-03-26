#include <iostream>

#include "ClientsInstance.hpp"
#include "Client.hpp"

#include "Server.hpp"
#include "Connection.hpp"
#include "DefaultParser.hpp"
#include "DefaultLogger.hpp"
#include "RequestEmitter.hpp"

ClientsInstance::ClientsInstance(bool useConnectionWrapper)
:   _useConnectionWrapper(useConnectionWrapper),
    _running(false)
{}

ClientsInstance::~ClientsInstance()
{
    if (this->_running)
        this->_thread.join();
}

void ClientsInstance::run(Modules::ptr modules, const Server::SocketsQueue &sockQueue)
{
    _modules = modules;
    this->_thread = std::thread(
        [sockQueue, this]()
        {
            std::cout << "starting new thread" << std::endl;
            // Instiate instance in thread memory
            Instance inst;

            inst.run(_modules, this->_useConnectionWrapper, sockQueue);
        }
    );
    this->_running = true;
}

void ClientsInstance::Instance::run(
    Modules::ptr                modules,
    bool                        useConnectionWrapper,
    const Server::SocketsQueue  &sockQueue
)
{
    std::vector<Client::ptr> clients;
    _modules = modules;

    while (!_modules->_isExit) {

        this->handleNewClient(sockQueue, clients, useConnectionWrapper);
        this->clientsLoop(clients);
    }
}

void ClientsInstance::Instance::handleNewClient(
    const Server::SocketsQueue &sockQueue,
    std::vector<Client::ptr> &clients,
    bool useConnectionWrapper
)
{
    if (clients.size() >= MAX_CLIENT)
        return;

    Socket::ptr sock;

    if (!sockQueue->pop(sock))
        return;

    std::unique_ptr<Zia::Module::IParser::IInstance> parser;
    Zia::ConnectionPtr conn;
    Zia::RequestEmitterPtr emitter;
    RequestWrapper::ptr requestWrapper(RequestWrapper::create());


    if (useConnectionWrapper && _modules->_connectionWrapper) {
        std::cout << "CONNECTIONWRAPPER" << std::endl;
        auto connection = Connection(sock);
        conn = _modules->_connectionWrapper->create(connection);
    } else
        conn = Connection::create(sock);
    emitter = RequestEmitter::create(requestWrapper);
    auto h = this->_modules->_handlers;
    Zia::LoggerPtr loggers = std::make_shared<Loggers>(_modules->_loggers);
    if (_modules->_parser)
        parser = _modules->_parser->create(*conn, *loggers, *emitter);
    else
        parser = DefaultParserInstance::create(*conn, *loggers, *emitter);


    clients.push_back(
        Client::create(
            sock,
            conn,
            parser,
            loggers,
            this->_modules->_handlers,
            emitter,
            requestWrapper
        )
    );

    std::cout << "GOT CLIENT" << std::endl;
}

void ClientsInstance::Instance::clientsLoop(std::vector<Client::ptr> &clients)
{
    auto it = clients.begin();

    while (it != clients.end()) {
        auto &cli = *it;

        if (!cli->isActive()) {
            it = clients.erase(it);
            continue;
        }
        cli->refresh(); // REFRESH CLIENT (PARSE, ...)
        ++it;
    }
}