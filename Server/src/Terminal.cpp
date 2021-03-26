/*
** EPITECH PROJECT, 2021
** Terminal.cpp
** File description:
** Terminal.cpp
*/

#include <iostream>
#include <sstream>
#include <algorithm>
#include "Terminal.hpp"
#include "Handler.hpp"
#include "DynamicLib.hpp"

Terminal::Terminal(Modules::ptr modules, const ParseArgs &args)
:   _modules(modules),
    _args(args),
    _config(this->_args.getConfigPath()),
    _httpInstance(_modules, this->_args.getHttpPort(), "http"),
    _httpsInstance(modules, this->_args.getHttpsPort(),"https")
{
    std::vector<std::string> v;
    this->refresh(v);
    this->load(v);

    this->startHTTP(v);
    this->startHTTPS(v);
}

Terminal::~Terminal()
{
    this->_httpInstance.join();
    this->_httpsInstance.join();
}

std::vector<std::string> Terminal::splitByChar(std::vector<std::string> tab, std::string str, char c)
{
    std::stringstream stream(str);
    std::string tmp;

    while (std::getline(stream, tmp, c))
        tab.push_back(tmp);
    return (tab);
}

void Terminal::printTab(std::vector<std::string> tab)
{
    for (auto &it : tab)
        std::cout << it << std::endl;
}

std::vector<std::string> Terminal::getCommand(std::string tmp)
{
    std::vector<std::string> tab;
    size_t idx;

    if ((idx = tmp.find_first_of(' ', 0)) == std::string::npos)
        return (splitByChar(tab, tmp, ','));
    tab.push_back(tmp.substr(0, (idx)));
    tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
    return (splitByChar(tab, tmp.erase(0, idx), ','));
}

void Terminal::run()
{
    std::string tmp;
    std::vector<std::string> tab;

    std::cout << "> ";

    while (std::getline(std::cin, tmp)) {
        tab = getCommand(tmp);
        //printTab(tab);
        if (tab.size() > 0 && tab[0] == "EXIT")
            break;
        for (size_t i = 0; i < _label.size() && tab.size() > 0; i++)
            if (tab[0] == _label[i])
                ((_ptr[i]))(this, tab);

        std::cout << "> ";
    }

    _modules->_isExit = true;
}

void Terminal::refresh(std::vector<std::string> &names)
{
    (void)names;
    _config.loadConfFile();
    _modules->_handlers.clear();
    _modules->_loggers.clear();
    std::cout << "Refreshed modules" << std::endl;
}

void Terminal::load(std::vector<std::string> &names)
{
    (void)names;
    _modules->_parser = DynamicLib<Zia::Module::IParser>(_config.getParser().getPath(), "createParser", _config.getParser().getConf()).GetDLib();
    _modules->_connectionWrapper = DynamicLib<Zia::Module::IConnectionWrapper>(_config.getConnectionWrapper().getPath(), "createConnectionWrapper", _config.getConnectionWrapper().getConf()).GetDLib();
    for (auto &inst : _config.getHandlers()) {
        auto h = DynamicLib<Zia::Module::IHandler>(inst.getPath(), "createHandler", inst.getConf()).GetDLib();
        if (h != nullptr)
            _modules->_handlers.push_back(h);
    }
    for (auto &inst : _config.getLoggers()) {
        auto l = DynamicLib<Zia::Module::ILogger>(inst.getPath(), "createLogger", inst.getConf()).GetDLib();
        if ((l) != nullptr) {
            _modules->_loggers.push_back(l);
        }
    }
    std::cout << "Loading..." << std::endl;
}

void Terminal::startHTTP(std::vector<std::string> &names)
{
    (void)names;

    if (this->_httpInstance.hasError())
        this->_httpInstance.join();

    if (this->_httpInstance.isRunning()) {
        std::cerr << "http instance already running." << std::endl;
        return;
    }

    this->_httpInstance.run();
}

void Terminal::startHTTPS(std::vector<std::string> &names)
{
    (void)names;

    if (this->_httpsInstance.hasError())
        this->_httpsInstance.join();

    if (this->_httpsInstance.isRunning()) {
        std::cerr << "https instance already running." << std::endl;
        return;
    }

    this->_httpsInstance.run();
}