/*
** EPITECH PROJECT, 2020
** zia
** File description:
** IModule
*/

#pragma once

#include <any>

class IModule {
public:
    virtual ~IModule() = default;
    virtual int getId() = 0;
};
