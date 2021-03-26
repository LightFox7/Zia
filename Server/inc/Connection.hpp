#pragma once

#include "DefaultLogger.hpp"
#include "Socket.hpp"

class Connection : public Zia::IConnection
{
    public:
        Connection(const Socket::ptr &socket);
        ~Connection() = default;

        size_t read(size_t buf_size, char *buf);

        size_t write(size_t buf_size, const char *buf);

        static Zia::ConnectionPtr create(const Socket::ptr &socket);

        void log(const std::string &str);

        const std::string& getRemoteIP(void) const;

        int getNativeSocket(void) const;

        Socket::ptr getSocketPtr(void) const;

    private:
        Socket::ptr _socket;
        std::string _remoteIP;
};