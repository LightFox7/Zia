/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** Config
*/

#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include "ModuleLoader.hpp"

using json = nlohmann::json;

class Config {
public:
    Config(std::string const &path = "");
    ~Config();
    void setPath(std::string const &path);
    std::string getPath(void) const;
    void loadConfFile(void);
    std::vector<ModuleLoader> getLoggers(void) const;
    ModuleLoader getConnectionWrapper(void) const;
    ModuleLoader getParser(void) const;
    std::vector<ModuleLoader> getHandlers(void) const;
    Json::Integer getHttpsPort(void) const;
    Json::Integer getHttpPort(void) const;

private:
    std::string _path;
    std::vector<ModuleLoader> _loggers;
    ModuleLoader _connection_wrapper;
    ModuleLoader _parser;
    std::vector<ModuleLoader> _handlers;
    Json::Integer _httpsPort;
    Json::Integer _httpPort;

    void parseConf(json const &config);
};
