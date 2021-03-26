#include "DefaultParser.hpp"

DefaultParserInstance::DefaultParserInstance(Zia::IInput &input, Zia::ILogger &log, Zia::IRequest::IEmitter &requestEmitter)
{
    (void)input;
    (void)log;
    (void)requestEmitter;
}

void DefaultParserInstance::parse()
{

}

std::unique_ptr<Zia::ParserInstance> DefaultParser::create(Zia::IInput &input, Zia::ILogger &log, Zia::IRequest::IEmitter &requestEmitter)
{
    return std::make_unique<DefaultParserInstance>(input, log, requestEmitter);
}

std::unique_ptr<Zia::ParserInstance> DefaultParserInstance::create(Zia::IInput &input, Zia::ILogger &log, Zia::IRequest::IEmitter &requestEmitter)
{
    return std::make_unique<DefaultParserInstance>(input, log, requestEmitter);
}