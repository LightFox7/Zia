/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** ModuleLoader
*/

#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <memory>

#include "Conf.hpp"

using namespace Zia;
using json = nlohmann::json;

class ModuleLoader {
public:
    ModuleLoader(std::string const &path = "", json const &conf = json::object());
    ~ModuleLoader();
    void setPath(const std::string &path);
    void setConf(IObject *conf);
    void setConf(const json &conf);
    const std::string &getPath(void) const;
    IConf &getConf(void);

private:
    std::string _path;
    std::shared_ptr<IConf> _conf;
};