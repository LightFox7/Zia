#include <iostream>
#include <boost/algorithm/string.hpp>

#include "Client.hpp"
#include "Request.hpp"
#include "debug.hpp"
#include "HttpHeaders.hpp"
#include "Response.hpp"
#include "DefaultLogger.hpp"
#include "Context.hpp"

Client::Client(
    const Socket::ptr                   &sock,
    Zia::ConnectionPtr                  &conn,
    Zia::ParserInstancePtr              &parser,
    Zia::LoggerPtr                      &logger,
    const std::vector<Zia::HandlerPtr>  &handlers,
    Zia::RequestEmitterPtr              &emitter,
    const RequestWrapper::ptr           &requestWrapper
)
:   _socket(sock),
    _connection(std::move(conn)),
    _parser(std::move(parser)),
    _logger(std::move(logger)),
    _handlers(handlers),
    _emitter(emitter),
    _requestWrapper(requestWrapper),
    _keepAlive(false)
{}

void Client::refresh()
{

    // try to parse a request
    this->_parser->parse();

    // unwrap request wrapped by Request Emitter, which is called by parser
    auto optionalRequest = this->_requestWrapper->unwrap();

    // No request : done
    if (!optionalRequest)
        return;

    std::cout << "GOT REQUEST" << std::endl;

    // We got a request : handle it
    this->handleRequest(optionalRequest->get());
}

void Client::handleRequest(const Zia::IRequest &request)
{
    std::cout << "url = " << request.getURL() << std::endl;
    // Check Connection: keep-alive
    this->checkConnectionHeader(request);

    // Init repsonse and context
    Response response;
    Context ctx;

    for (auto &handler : this->_handlers) {
        handler->handle(request, response, ctx, *this->_logger);
        // if handler abort, breka loop
        if (response.isPipelineAborted())
            break;
    }

    if (request.getMethod() != "HEAD" && response.getBody() == nullptr) {
        std::string strBody("hello from zia ! Edit config.json to set handlers");
        response.setBody(std::vector<char>(strBody.begin(), strBody.end()));
        response.setHeader("Content-type", "text/plain");
    }

    if (request.getMethod() == "HEAD")
        response.setNullBody();

    // Set http Connection header
    this->setConnectionHeader(response);

    // Serialize response
    std::string rawResponse = response.serialize();

    // Write response to socket
    size_t writeSize = this->_connection->write(rawResponse.size(), rawResponse.c_str());

    if (writeSize != rawResponse.size())
        std::cout << "[WARNING] : response size = " << rawResponse.size() << ", writed size = " << writeSize << std::endl;

    // Disconnect client if Connection: keep-alive header not set
    if (!this->_keepAlive)
        this->_socket->disconnect();
}

bool Client::isActive() const
{
    return this->_socket->isActive();
}

void Client::setConnectionHeader(Zia::IResponse &response)
{
    std::string connectionValue(
        this->_keepAlive ?
        KEEP_ALIVE :
        CLOSE
    );

    response.setHeader(CONNECTION, connectionValue);
}

void Client::checkConnectionHeader(const Zia::IRequest &request)
{
    auto connectionValue = request.getHeader(CONNECTION);

    this->_keepAlive = connectionValue != nullptr && \
        boost::to_lower_copy(*connectionValue) == KEEP_ALIVE;
}

Client::ptr Client::create(
    const Socket::ptr                   &sock,
    Zia::ConnectionPtr                  &conn,
    Zia::ParserInstancePtr              &parser,
    Zia::LoggerPtr                      &logger,
    const std::vector<Zia::HandlerPtr>  &handlers,
    Zia::RequestEmitterPtr              &emitter,
    const RequestWrapper::ptr           &requestWrapper
)
{
    return std::make_unique<Client>(
        sock,
        conn,
        parser,
        logger,
        handlers,
        emitter,
        requestWrapper
    );
}