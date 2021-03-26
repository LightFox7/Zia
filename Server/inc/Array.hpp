/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** Array
*/

#pragma once

#include <nlohmann/json.hpp>

#include "Zia.hpp"
#include "Object.hpp"

using namespace Zia;
using namespace Zia::Json;

class Array : public IArray
{
public:
    Array();
    Array(nlohmann::json const &data);
	~Array();
	size_t getSize(void) const;
	void remove(size_t index);
    std::optional<Json::Number> getNumber(size_t i) const;
	std::optional<Json::Integer> getInteger(size_t i) const;
    std::optional<Json::String> getString(size_t i) const;
	std::optional<Json::Bool> getBool(size_t i) const;
	bool isNull(size_t i) const;
	bool isUndefined(size_t i) const;
	const IObject* getObject(size_t i) const;
	const IArray* getArray(size_t i) const;
	void setNumber(size_t i, Number value);
    void setInteger(size_t i, Integer value);
    void setString(size_t i, const String &value);
    void setBool(size_t i, Bool value);
    void setNull(size_t i);
    void setUndefined(size_t i);
    IObject* getObject(size_t i);
    IArray* getArray(size_t i);
    IObject& createEmptyObject(size_t i);
    IArray& createEmptyArray(size_t i);
    void clear(void);

private:
    nlohmann::json _data;
    std::map<size_t, Array> _arrays;
    std::map<size_t, Object> _objects;
    std::map<size_t, Json::Bool> _bools;
    std::map<size_t, Json::Integer> _integers;
    std::map<size_t, Json::Number> _numbers;
    std::map<size_t, Json::String> _strings;
    std::vector<size_t> _nullvalues;
};