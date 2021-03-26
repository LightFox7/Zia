/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** SSLConnection
*/

#pragma once

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/opensslv.h>
#include "Zia.hpp"
#include "Socket.hpp"

class SSLConnection : public Zia::IConnection
{
    public:
        SSLConnection(int fdSocket, std::string remoteIP);
        ~SSLConnection();

        size_t read(size_t buf_size, char *buf);
        size_t write(size_t buf_size, const char *buf);

        const std::string& getRemoteIP(void) const;
        int getNativeSocket(void) const;
        void log(const std::string &str);

        bool InitSSL();
        bool UseCertificate();

    private:
        SSL_CTX* _ctx;
	    SSL* _ssl;
        int _nativeFd;
        std::string _remoteIP;
        std::string _certificateFile;
		std::string _certificateKey;
};