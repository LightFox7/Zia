#include "Zia.hpp"

namespace Zia
{
    using ParserInstance = Module::IParser::IInstance;
    using ParserInstancePtr = std::unique_ptr<ParserInstance>;
    using ParserPtr = std::shared_ptr<Module::IParser>;

    using ConnectionPtr = std::unique_ptr<IConnection>;

    using LoggerPtr = std::shared_ptr<Module::ILogger>;

    using RequestEmitterPtr = std::shared_ptr<IRequest::IEmitter>;

    using ConnectionWrapperPtr = std::shared_ptr<Module::IConnectionWrapper>;

    using HandlerPtr = std::shared_ptr<Module::IHandler>;

    using RequestPtr = std::shared_ptr<IRequest>;

    using RequestRef = std::reference_wrapper<const IRequest>;
};