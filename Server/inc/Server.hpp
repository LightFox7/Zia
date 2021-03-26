#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Client.hpp"
#include "SafeQueue.hpp"

class Server
{
    public:
        using SocketsQueue = std::shared_ptr<SafeQueue<Socket::ptr>>;

        Server(uint16_t port, const SocketsQueue &sockQueue);
        ~Server();

        void listenAndServe();

    private:
        uint16_t _port;
        boost::asio::io_service _ios;
        tcp::acceptor _acceptor;
        bool _running;
        SocketsQueue _socketsQueue;
        boost::thread _th;

        void accept();
        void acceptHandler(Socket::ptr socket, const boost::system::error_code &error);
};