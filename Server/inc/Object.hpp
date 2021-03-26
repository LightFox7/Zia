/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** Object
*/

#pragma once

#include <nlohmann/json.hpp>

#include "Zia.hpp"

using namespace Zia;
using namespace Zia::Json;

class Array;

class Object : public IObject {
public:
    Object();
    Object(nlohmann::json const &data);
    ~Object();
    std::vector<std::string> getKeys(void) const;
    std::optional<Json::Number> getNumber(const std::string& i) const;
    std::optional<Json::String> getString(const std::string& i) const;
	std::optional<Json::Integer> getInteger(const std::string& i) const;
	std::optional<Json::Bool> getBool(const std::string& i) const;
	bool isNull(const std::string& i) const;
	bool isUndefined(const std::string& i) const;
	const IObject* getObject(const std::string& i) const;
	const IArray* getArray(const std::string& i) const;
	void setNumber(const std::string& i, Number value);
    void setInteger(const std::string& i, Integer value);
    void setString(const std::string& i, const String &value);
    void setBool(const std::string& i, Bool value);
    void setNull(const std::string& i);
    void setUndefined(const std::string& i);
    IObject* getObject(const std::string& i);
    IArray* getArray(const std::string& i);
    IObject& createEmptyObject(const std::string& i);
    IArray& createEmptyArray(const std::string& i);
    void clear(void);

private:
    nlohmann::json _data;
    std::map<std::string, Array> _arrays;
    std::map<std::string, Object> _objects;
    std::map<std::string, Json::Bool> _bools;
    std::map<std::string, Json::Integer> _integers;
    std::map<std::string, Json::Number> _numbers;
    std::map<std::string, Json::String> _strings;
    std::vector<std::string> _nullvalues;
};

#include "Array.hpp"