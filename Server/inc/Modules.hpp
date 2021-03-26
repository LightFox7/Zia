#pragma once

#include "DynamicLib.hpp"
#include <atomic>
#include <memory>

class Modules
//  : public Zia::Module::ILogger,
//                 public Zia::Module::IConnectionWrapper,
//                 public Zia::Module::IParser,
//                 public Zia::Module::IHandler
{
    public:

        using ptr = std::shared_ptr<Modules>;

        Modules();

        // void log(const std::string &str);
        // void handle(const Zia::IRequest &req, Zia::IResponse &res, Zia::IContext &ctx, Zia::ILogger &log);
        // std::unique_ptr<Zia::IConnection> create(Zia::IConnection &connection);
        // std::unique_ptr<Zia::ParserInstance> create(Zia::IInput &input, Zia::ILogger &log, Zia::IRequest::IEmitter &requestEmitter);

        static ptr create();

        std::vector<Zia::LoggerPtr> _loggers;
        Zia::ConnectionWrapperPtr _connectionWrapper;
        Zia::ParserPtr _parser;
        std::vector<Zia::HandlerPtr> _handlers;
        std::atomic<bool> _isExit;
};