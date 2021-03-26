/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** ModuleLoader
*/

#include "ModuleLoader.hpp"

ModuleLoader::ModuleLoader(std::string const &path, json const &conf) : _path(path)
{
    Json::IObject *obj = new Object(conf);

    _conf = std::make_shared<Conf>();
    _conf->write(*obj);
    delete obj;
}

ModuleLoader::~ModuleLoader()
{
}

void ModuleLoader::setPath(std::string const &path)
{
    _path = path;
}

void ModuleLoader::setConf(json const &conf)
{
    Json::IObject *obj = new Object(conf);
    _conf->write(*obj);
    delete obj;
}

void ModuleLoader::setConf(IObject *conf)
{
    _conf->write(*conf);
}


const std::string &ModuleLoader::getPath(void) const
{
    return (_path);
}

IConf &ModuleLoader::getConf(void)
{
    return (*_conf);
}