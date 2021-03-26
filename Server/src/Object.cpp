/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** Object
*/

#include "Object.hpp"

Object::Object()
{
}

Object::Object(nlohmann::json const &data) : _data(data)
{
    if (!data.is_object()) {
        _data = nlohmann::json::object();
        return;
    }
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it.value().is_array())
            _arrays.emplace(it.key(), Array(it.value()));
        else if (it.value().is_object())
            _objects.emplace(it.key(), Object(it.value()));
        else if (it.value().is_binary())
            _bools.emplace(it.key(), it.value());
        else if (it.value().is_number_integer())
            _integers.emplace(it.key(), it.value());
        else if (it.value().is_number())
            _numbers.emplace(it.key(), it.value());
        else if (it.value().is_string())
            _strings.emplace(it.key(), it.value());
        else if (it.value().is_null())
            _nullvalues.push_back(it.key());
    }
}

Object::~Object()
{
}

std::vector<std::string> Object::getKeys(void) const
{
    std::vector<std::string> vec;

    if (_data.is_object()) {
        for (auto it = _data.begin(); it != _data.end(); ++it) {
            vec.push_back(it.key());
        }
    }
    for (auto it = _objects.begin(); it != _objects.end(); ++it) {
        if (std::find(vec.begin(), vec.end(), it->first) != vec.end())
            vec.push_back(it->first);
    }
    for (auto it = _arrays.begin(); it != _arrays.end(); ++it) {
        if (std::find(vec.begin(), vec.end(), it->first) != vec.end())
            vec.push_back(it->first);
    }
    return (vec);
}

std::optional<Json::Number> Object::getNumber(const std::string& i) const
{
    if (_data.contains(i) && _data[i].is_number())
        return (_data[i]);
    return (std::nullopt);
}

std::optional<Json::Integer> Object::getInteger(const std::string& i) const
{
    if (_data.contains(i) && _data[i].is_number_integer())
        return (_data[i]);
    return (std::nullopt);
}

std::optional<Json::String> Object::getString(const std::string& i) const
{
    if (_data.contains(i) && _data[i].is_string())
        return (_data[i]);
    return (std::nullopt);
}

std::optional<Json::Bool> Object::getBool(const std::string& i) const
{
    if (_data.contains(i) && _data[i].is_boolean())
        return (_data[i]);
    return (std::nullopt);
}

bool Object::isNull(const std::string& i) const
{
    if (_data.contains(i) && _data[i].is_null())
        return true;
    return false;
}

bool Object::isUndefined(const std::string& i) const
{
    if (!_data.contains(i))
        return true;
    return false;
}

const IObject* Object::getObject(const std::string& i) const
{
    if (_objects.find(i) != _objects.end())
        return (&_objects.at(i));
    return (nullptr);
}

const IArray* Object::getArray(const std::string& i) const
{
    if (_arrays.find(i) != _arrays.end())
        return (&_arrays.at(i));
    return (nullptr);
}

void Object::setNumber(const std::string& i, Number value)
{
    _data[i] = value;
}

void Object::setInteger(const std::string& i, Integer value)
{
    _data[i] = value;
}

void Object::setString(const std::string& i, const String &value)
{
    _data[i] = value;
}

void Object::setBool(const std::string& i, Bool value)
{
    _data[i] = value;
}

void Object::setNull(const std::string& i)
{
    _data[i] = nullptr;
}

void Object::setUndefined(const std::string& i)
{
    _data.erase(i);
}

IObject* Object::getObject(const std::string& i)
{
    if (_objects.find(i) != _objects.end())
        return (&_objects.at(i));
    return (nullptr);
}

IArray* Object::getArray(const std::string& i)
{
    if (_arrays.find(i) != _arrays.end())
        return (&_arrays.at(i));
    return (nullptr);
}

IObject& Object::createEmptyObject(const std::string& i)
{
    _objects.emplace(i, Object());
    return _objects.at(i);
}

IArray& Object::createEmptyArray(const std::string& i)
{
    _arrays.emplace(i, Array());
    return _arrays.at(i);
}

void Object::clear(void)
{
    if (_data.is_object())
        _data.clear();
}
