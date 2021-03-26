/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** SSLConnection
*/

#include "SSLConnection.hpp"
#include "Connection.hpp"
#include <iostream>

SSLConnection::SSLConnection(int fdSocket, std::string remoteIP)
:   _nativeFd(fdSocket),
    _remoteIP(remoteIP)
{
    OPENSSL_init_ssl(0, NULL);
    SSLeay_add_ssl_algorithms();
    SSL_load_error_strings();
    _ctx = SSL_CTX_new(SSLv23_server_method());
    _certificateFile = "../modules/SSL/certif/cert.pem";
    _certificateKey = "../modules/SSL/certif/key.pem";
    UseCertificate();
    InitSSL();
}

bool SSLConnection::InitSSL()
{
    bool no_error = false;
    int err = 0;

    _ssl = SSL_new(_ctx);
    if (!_ssl) {
        std::cout << "Error creating SSL" << std::endl;
        return (false);
    }
    SSL_set_fd(_ssl, _nativeFd);
    do {
        err = SSL_accept(_ssl);
        switch(SSL_get_error(_ssl, err)) {
            case SSL_ERROR_NONE:
                break;
            case SSL_ERROR_ZERO_RETURN:
            case SSL_ERROR_WANT_READ:
                break;
            case SSL_ERROR_WANT_WRITE:
                break;
            case SSL_ERROR_WANT_CONNECT:
            case SSL_ERROR_WANT_ACCEPT:
            case SSL_ERROR_WANT_X509_LOOKUP:
            case SSL_ERROR_SYSCALL:
            case SSL_ERROR_SSL:
            default:
                no_error = false;
                break;
        }
    } while (err < 0 && no_error);
    return (true);
}

bool SSLConnection::UseCertificate()
{
    if (SSL_CTX_use_certificate_file(_ctx, _certificateFile.data(), SSL_FILETYPE_PEM) < 1) {
        std::cerr << "SSL_CTX_use_certificate_file null" << std::endl;
        ERR_print_errors_fp(stderr);
        return (false);
    }
    if (SSL_CTX_use_PrivateKey_file(_ctx, _certificateKey.data(), SSL_FILETYPE_PEM) < 1) {
        std::cerr << "SSL_CTX_use_PrivateKey_file null" << std::endl;
        ERR_print_errors_fp(stderr);
        return (false);
    }
    // if (!SSL_CTX_check_private_key(_ctx)) {
    //     std::cerr << "Private key does not match the public certificate" << std::endl;
    //     ERR_print_errors_fp(stderr);
    //     return (false);
    // }
    return (true);
}

size_t SSLConnection::read(size_t buf_size, char *buf)
{
    int bytes = 0;

    bytes = SSL_read(_ssl, buf, buf_size);
    if (bytes < 0) {
        int err = SSL_get_error(_ssl, bytes);
        if (err == SSL_ERROR_ZERO_RETURN || err == SSL_ERROR_SYSCALL || err == SSL_ERROR_SSL || err == SSL_ERROR_WANT_WRITE || err == SSL_ERROR_WANT_READ)
            return 0;
    }
    return (bytes);
}

size_t SSLConnection::write(size_t buf_size, const char *buf)
{
    int bytes = 0;

    bytes = SSL_write(_ssl, buf, buf_size);
    if (bytes < 0) {
        int err = SSL_get_error(_ssl, bytes);
        switch (err) {
            case SSL_ERROR_WANT_WRITE:
                return 0;
            case SSL_ERROR_WANT_READ:
                return 0;
            case SSL_ERROR_ZERO_RETURN:
            case SSL_ERROR_SYSCALL:
            case SSL_ERROR_SSL:
            default:
                return 0;
        }
    }
    return (bytes);
}

void SSLConnection::log(const std::string &str)
{
    (void)str;
}

const std::string& SSLConnection::getRemoteIP(void) const
{
    return this->_remoteIP;
}

int SSLConnection::getNativeSocket(void) const
{
    return _nativeFd;
}

SSLConnection::~SSLConnection()
{
    SSL_free(_ssl);
    SSL_CTX_free(_ctx);
    EVP_cleanup();
}