/*
** EPITECH PROJECT, 2021
** Terminal.hpp
** File description:
** Terminal.hpp
*/

#include <functional>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
#endif

#include "Modules.hpp"
#include "DynamicLib.hpp"
#include "Zia.hpp"
#include "Config.hpp"
#include "ZiaInstance.hpp"
#include "HttpCore.hpp"
#include "HttpsCore.hpp"
#include "ParseArgs.hpp"

class Terminal {

    public:

        Terminal(Modules::ptr modules, const ParseArgs &args);

        ~Terminal();


        void run();

        void refresh(std::vector<std::string> &names);

        void load(std::vector<std::string> &names);

        void startHTTP(std::vector<std::string> &names);

        void startHTTPS(std::vector<std::string> &names);


        std::vector<std::string> splitByChar(std::vector<std::string> tab, std::string str, char c);

        std::vector<std::string> getCommand(std::string tmp);

        void printTab(std::vector<std::string> tab);


    private:
        Modules::ptr _modules;
        ParseArgs _args;
        Config _config;
        ZiaInstance<HttpCore> _httpInstance;
        ZiaInstance<HttpsCore> _httpsInstance;

        const std::vector<std::string> _label = {
            "REFRESH",
            "LOAD",
            "start_http",
            "start_https"
        };

        std::vector<std::function<void(Terminal*, std::vector<std::string>&)>> _ptr = {
            &Terminal::refresh,
            &Terminal::load,
            &Terminal::startHTTP,
            &Terminal::startHTTPS
        };
};