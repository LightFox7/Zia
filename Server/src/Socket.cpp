#include <boost/make_shared.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

#include "Socket.hpp"

Socket::Socket(boost::asio::io_service &ios)
:   _socket(ios),
    _active(true)
{

}

Socket::ptr Socket::create(boost::asio::io_service &ios)
{
    return boost::make_shared<Socket>(ios);
}

void Socket::makeNonBlocking()
{
    this->_socket.non_blocking(true);
}

tcp::socket &Socket::getSocket()
{
    return this->_socket;
}

bool Socket::isActive() const
{
    return this->_active;
}

void Socket::disconnect()
{
    this->_active = false;
}

size_t Socket::receive(size_t size, char *buf)
{
    if (!size || buf == nullptr)
        return 0;

    boost::system::error_code error;

    size_t ret = this->_socket.read_some(boost::asio::buffer(buf, size), error);

    if (error && error != boost::asio::error::would_block)
        this->_active = false;

    return ret;
}

size_t Socket::send(size_t size, const char *buf)
{
    if (!size || buf == nullptr)
        return 0;

    boost::system::error_code error;

    size_t ret = this->_socket.write_some(boost::asio::buffer(buf, size), error);

    if (error && error != boost::asio::error::would_block)
        this->_active = false;

    return ret;
}

int Socket::getNativeFdSocket(void)
{
    _nativeFd = this->_socket.native_handle();
    std::cout << "native in Socket: " << _nativeFd << std::endl;
    return _nativeFd;
}