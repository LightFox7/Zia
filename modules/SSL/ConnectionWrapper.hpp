/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** ConnectionWrapper
*/

#pragma once

#include "Zia.hpp"

class ConnectionWrapper : public Zia::Module::IConnectionWrapper
{
    public:
        ConnectionWrapper();
        ~ConnectionWrapper();
        std::unique_ptr<Zia::IConnection> create(Zia::IConnection &connection);
};