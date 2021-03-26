/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** Conf
*/

#pragma once

#include "Object.hpp"

using namespace Zia;

class Conf : public IConf {
public:
    Conf() {};
    std::unique_ptr<Json::IObject> read(void) const {
        return std::make_unique<Object>(_obj);;
    }
	void write(const Json::IObject &jsonObject) {
        auto obj = dynamic_cast<const Object*>(&jsonObject);
        if (obj)
            _obj = *obj;
    }

private:
    Object _obj;
};