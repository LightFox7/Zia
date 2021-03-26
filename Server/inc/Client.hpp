#pragma once

#include "ZiaTypes.hpp"
#include "Socket.hpp"
#include "RequestEmitter.hpp"
#include "RequestWrapper.hpp"

class Client
{
    public:
        using ptr = std::unique_ptr<Client>;

        Client(
            const Socket::ptr                   &sock,
            Zia::ConnectionPtr                  &conn,
            Zia::ParserInstancePtr              &parser,
            Zia::LoggerPtr                      &logger,
            const std::vector<Zia::HandlerPtr>  &handlers,
            Zia::RequestEmitterPtr              &emitter,
            const RequestWrapper::ptr           &requestWrapper
        );
        ~Client() = default;

        void refresh();

        bool isActive() const;

        static ptr create(
            const Socket::ptr                   &sock,
            Zia::ConnectionPtr                  &conn,
            Zia::ParserInstancePtr              &parser,
            Zia::LoggerPtr                      &logger,
            const std::vector<Zia::HandlerPtr>  &handlers,
            Zia::RequestEmitterPtr              &emitter,
            const RequestWrapper::ptr           &requestWrapper
        );

    private:
        Socket::ptr _socket;
        Zia::ConnectionPtr _connection;
        Zia::ParserInstancePtr _parser;
        Zia::LoggerPtr _logger;
        std::vector<Zia::HandlerPtr> _handlers;
        Zia::RequestEmitterPtr _emitter;
        RequestWrapper::ptr _requestWrapper;
        bool _keepAlive;

        void handleRequest(const Zia::IRequest &request);
        void setConnectionHeader(Zia::IResponse &response);
        void checkConnectionHeader(const Zia::IRequest &request);
};