/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** ParseArgs
*/

#pragma once

#include <string>
#include <stdexcept>

class ParseArgs {
public:
    ParseArgs(int ac, char **av) {
        if (ac > 1)
            _configPath = av[1];
        else
            _configPath = "config.json";
        if (ac > 2) {
            try {
                _httpPort = std::stoi(av[2]);
            } catch (std::invalid_argument& e) {
                _httpPort = 8080;
            } catch (std::out_of_range& e) {
                _httpPort = 8080;
            }
        }
        else
            _httpPort = 8080;
        if (ac > 3) {
            try {
                _httpsPort = std::stoi(av[3]);
            } catch (std::invalid_argument& e) {
                _httpsPort = 4343;
            } catch (std::out_of_range& e) {
                _httpsPort = 4343;
            }
        }
        else
            _httpsPort = 4343;

        if (_httpPort == _httpsPort)
            throw std::runtime_error("same port used for http and https");
    };
    ~ParseArgs() = default;
    std::string getConfigPath() const {
        return (_configPath);
    }
    int getHttpPort() const {
        return (_httpPort);
    }
    int getHttpsPort() const {
        return (_httpsPort);
    }

private:
    std::string _configPath;
    int _httpPort;
    int _httpsPort;
};
