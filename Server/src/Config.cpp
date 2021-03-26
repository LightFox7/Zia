/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** Config
*/

#include "Config.hpp"

Config::Config(std::string const &path) : _path(path)
{
}

Config::~Config()
{
}

void Config::setPath(std::string const &path)
{
    _path = path;
}

std::string Config::getPath(void) const
{
    return (_path);
}

void Config::loadConfFile(void)
{
    json conf;
    std::ifstream conf_file(_path);

    if (!conf_file)
        return;
    try {
        conf_file >> conf;
    } catch(const json::parse_error &) {
        return;
    }
    _loggers.clear();
    _handlers.clear();
    parseConf(conf);
}

void Config::parseConf(json const &conf)
{
    json loggers;
    json connection_wrapper;
    json parser;
    json handlers;

    if (!conf.is_object())
        return;
    if (conf.find("connection_wrapper") != conf.end() && conf["connection_wrapper"].is_object())
        connection_wrapper = conf["connection_wrapper"];
    if (conf.find("parser") != conf.end() && conf["parser"].is_object())
        parser = conf["parser"];
    if (conf.find("loggers") != conf.end() && conf["loggers"].is_array())
        loggers = conf["loggers"];
    if (conf.find("handlers") != conf.end() && conf["handlers"].is_array())
        handlers = conf["handlers"];
    if (conf.find("httpPort") != conf.end() && conf["httpPort"].is_number_integer())
        _httpPort = conf["httpPort"];
    if (conf.find("httpsPort") != conf.end() && conf["httpsPort"].is_number_integer())
        _httpsPort = conf["httpsPort"];
    if (loggers.is_array()) {
        for (auto it = loggers.begin(); it != loggers.end(); ++it) {
            if ((*it)["path"].is_string())
                _loggers.push_back(ModuleLoader((*it)["path"], (*it)["conf"]));
            else
                _loggers.push_back(ModuleLoader("", (*it)["conf"]));
        }
    }
    if (connection_wrapper.is_object() && connection_wrapper["path"].is_string()) {
        _connection_wrapper = ModuleLoader(connection_wrapper["path"], connection_wrapper["conf"]);
    } else if (connection_wrapper.is_object()) {
        _connection_wrapper = ModuleLoader("", connection_wrapper["conf"]);
    }
    if (parser.is_object() && parser["path"].is_string()) {
        _parser = ModuleLoader(parser["path"], parser["conf"]);
    } else if (parser.is_object()) {
        _parser = ModuleLoader("", parser["conf"]);
    }
    if (handlers.is_array()) {
        for (auto it = handlers.begin(); it != handlers.end(); ++it) {
            if ((*it)["path"].is_string())
                _handlers.push_back(ModuleLoader((*it)["path"], (*it)["conf"]));
            else
                _handlers.push_back(ModuleLoader("", (*it)["conf"]));
        }
    }
}

std::vector<ModuleLoader> Config::getLoggers(void) const
{
    return (_loggers);
}

ModuleLoader Config::getConnectionWrapper(void) const
{
    return (_connection_wrapper);
}

ModuleLoader Config::getParser(void) const
{
    return (_parser);
}

std::vector<ModuleLoader> Config::getHandlers(void) const
{
    return (_handlers);
}

Json::Integer Config::getHttpsPort(void) const
{
    return (_httpsPort);
}

Json::Integer Config::getHttpPort(void) const
{
    return (_httpPort);
}