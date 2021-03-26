#include "Connection.hpp"
#include "debug.hpp"

Connection::Connection(const Socket::ptr &socket)
:   _socket(socket),
    _remoteIP(socket->getSocket().remote_endpoint().address().to_string())
{}

size_t Connection::read(size_t buf_size, char *buf)
{
    return this->_socket->receive(buf_size, buf);
}

size_t Connection::write(size_t buf_size, const char *buf)
{
    return this->_socket->send(buf_size, buf);
}

Zia::ConnectionPtr Connection::create(const Socket::ptr &socket)
{
    return std::make_unique<Connection>(socket);
}

void Connection::log(const std::string &str)
{
    (void)str;
}

const std::string& Connection::getRemoteIP(void) const
{
    return this->_remoteIP;
}

int Connection::getNativeSocket(void) const
{
    return _socket->getNativeFdSocket();
}