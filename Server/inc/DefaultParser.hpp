#pragma once

#include "ZiaTypes.hpp"

class DefaultParser : public Zia::Module::IParser
{
    public:
        DefaultParser() = default;
        ~DefaultParser() = default;

        std::unique_ptr<Zia::ParserInstance> create(Zia::IInput &input, Zia::ILogger &log, Zia::IRequest::IEmitter &requestEmitter);
};

class DefaultParserInstance : public Zia::ParserInstance
{
    public:
        DefaultParserInstance(Zia::IInput &input, Zia::ILogger &log, Zia::IRequest::IEmitter &requestEmitter);
        ~DefaultParserInstance() = default;

        void parse();

        static Zia::ParserInstancePtr create(Zia::IInput &input, Zia::ILogger &log, Zia::IRequest::IEmitter &requestEmitter);
};