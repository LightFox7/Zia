/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** Array
*/

#include "Array.hpp"

Array::Array()
{
}

Array::Array(nlohmann::json const &data) : _data(data)
{
    if (!_data.is_array()) {
        _data = nlohmann::json::array();
        return;
    }
    for (size_t i = 0; i < _data.size(); i++) {
        if (_data[i].is_array())
            _arrays.emplace(i, Array(_data[i]));
        else if (_data[i].is_object())
            _objects.emplace(i, Object(_data[i]));
        else if (_data[i].is_binary())
            _bools.emplace(i, _data[i]);
        else if (_data[i].is_number_integer())
            _integers.emplace(i, _data[i]);
        else if (_data[i].is_number())
            _numbers.emplace(i, _data[i]);
        else if (_data[i].is_string())
            _strings.emplace(i, _data[i]);
        else if (_data[i].is_null())
            _nullvalues.push_back(i);
    }
}

Array::~Array()
{
}

size_t Array::getSize(void) const
{
    if (_data.is_array())
        return (_data.size());
    return (_data);
}

void Array::remove(size_t index)
{
    if (_data.is_array() && _data.size() > index)
        _data.erase(index);
}

std::optional <Json::Number> Array::getNumber(size_t i) const
{
    if (_data.size() > i && _data[i].is_number())
        return (_data[i]);
    return (std::nullopt);
}

std::optional<Json::Integer> Array::getInteger(size_t i) const
{
    if (_data.size() > i && _data[i].is_number_integer())
        return (_data[i]);
    return (std::nullopt);
}

std::optional<Json::String> Array::getString(size_t i) const
{
    if (_data.size() > i && _data[i].is_string())
        return (_data[i]);
    return (std::nullopt);
}

std::optional<Json::Bool> Array::getBool(size_t i) const
{
    if (_data.size() > i && _data[i].is_boolean())
        return (_data[i]);
    return (std::nullopt);
}

bool Array::isNull(size_t i) const
{
    if (_data.size() > i && _data[i].is_null())
        return true;
    return false;
}

bool Array::isUndefined(size_t i) const
{
    if (_data.size() > i)
        return true;
    return false;
}

const IObject* Array::getObject(size_t i) const
{
    if (_objects.find(i) != _objects.end())
        return (&_objects.at(i));
    return (nullptr);
}

const IArray* Array::getArray(size_t i) const
{
    if (_arrays.find(i) != _arrays.end())
        return (&_arrays.at(i));
    return (nullptr);
}

void Array::setNumber(size_t i, Number value) {
    _data[i] = value;
}

void Array::setInteger(size_t i, Integer value) {
    _data[i] = value;
}

void Array::setString(size_t i, const String &value) {
    _data[i] = value;
}

void Array::setBool(size_t i, Bool value) {
    _data[i] = value;
}

void Array::setNull(size_t i)
{
    _data[i] = nullptr;
}

void Array::setUndefined(size_t i)
{
    if (_data.size() > i)
        _data.erase(i);
}

IObject* Array::getObject(size_t i)
{
    if (_objects.find(i) != _objects.end())
        return (&_objects.at(i));
    return (nullptr);
}

IArray* Array::getArray(size_t i)
{
    if (_arrays.find(i) != _arrays.end())
        return (&_arrays.at(i));
    return (nullptr);
}

IObject& Array::createEmptyObject(size_t i)
{
    _objects.emplace(i, Object());
    return _objects.at(i);
}

IArray& Array::createEmptyArray(size_t i)
{
    _arrays.emplace(i, Array());
    return _arrays.at(i);
}

void Array::clear(void)
{
    if (_data.is_array())
        _data.clear();
}
