#include <iostream>
#include <boost/thread.hpp>

#include "Server.hpp"
#include "Connection.hpp"
#include "DefaultParser.hpp"
#include "DefaultLogger.hpp"
#include "RequestEmitter.hpp"

Server::Server(uint16_t port, const SocketsQueue &sockQueue)
:   _port(port),
    _ios(),
    _acceptor(this->_ios, tcp::endpoint(tcp::v4(), port)),
    _running(false),
    _socketsQueue(sockQueue)
{}

Server::~Server()
{
    if (this->_running) {
        this->_ios.stop();
        this->_th.join();
    }
}

void Server::listenAndServe()
{
    this->accept();

    std::clog << "Server listening on 0.0.0.0:" << this->_port << std::endl;

    this->_th = boost::thread(
        boost::bind(
            &boost::asio::io_service::run,
            boost::ref(this->_ios)
        )
    );

    this->_running = true;
}

void Server::accept()
{
    Socket::ptr sock = Socket::create(this->_ios);

    this->_acceptor.async_accept(
        sock->getSocket(),
        boost::bind(
            &Server::acceptHandler,
            this,
            sock,
            boost::asio::placeholders::error
        )
    );
}

void Server::acceptHandler(Socket::ptr socket, const boost::system::error_code &error)
{
    if (error)
        throw std::runtime_error(error.message());

    socket->makeNonBlocking();

    this->_socketsQueue->push(socket);

    this->accept();
}