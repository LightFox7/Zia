/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ConnectionWrapper
*/

#include "ConnectionWrapper.hpp"
#include "SSLConnection.hpp"
#include <iostream>

ConnectionWrapper::ConnectionWrapper()
{

}

std::unique_ptr<Zia::IConnection> ConnectionWrapper::create(Zia::IConnection &connection)
{
    return (std::make_unique<SSLConnection>(connection.getNativeSocket(), connection.getRemoteIP()));
}

ConnectionWrapper::~ConnectionWrapper()
{

}

extern "C" {

ZIA_EXPORT_SYMBOL Zia::Module::IConnectionWrapper* createConnectionWrapper(Zia::IConf &conf)
{
    (void)conf;
    return (new ConnectionWrapper());
}

}