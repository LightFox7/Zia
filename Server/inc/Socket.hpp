#pragma once

#include <queue>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

#define BUF_SIZE 16

using boost::asio::ip::tcp;

class Socket : public boost::enable_shared_from_this<Socket>
{
    public:
        using ptr = boost::shared_ptr<Socket>;

        Socket(boost::asio::io_service &ios);
        ~Socket() = default;

        static ptr create(boost::asio::io_service &ios);

        void makeNonBlocking();
        tcp::socket &getSocket();

        bool isActive() const;
        void disconnect();

        size_t send(size_t size, const char *buf);
        size_t receive(size_t size, char *buf);

        int getNativeFdSocket(void);

    private:
        int _nativeFd;
        tcp::socket _socket;
        bool _active;
};