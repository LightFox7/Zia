/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** Log
*/

#pragma once

#include <fstream>
#include <string>

#include "Zia.hpp"

class FileLogger : public Zia::ILogger {
public:
    FileLogger(std::string const &path);
    ~FileLogger();
    void log(const std::string &str);

private:
    std::string _path;
};

extern "C" {

ZIA_EXPORT_SYMBOL Zia::ILogger* createLogger(Zia::IConf &conf) {
    std::string path = "log.txt";
    auto obj = conf.read();

    if (obj->getString("path") != std::nullopt)
        path =  obj->getString("path").value();
    return (new FileLogger(path));
}

}