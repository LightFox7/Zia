/*
** EPITECH PROJECT, 2021
** Request.cpp
** File description:
** Request.cpp
*/

#include <iostream>
#include "Request.hpp"

Request::Request() : _body(nullptr) {}

Request::~Request()
{
    if (this->_body != nullptr)
        delete this->_body;
}

void Request::reset()
{
    if (this->_body != nullptr) {
        delete this->_body;
        this->_body = nullptr;
    }

    this->_Header_value.clear();
    this->_Param_value.clear();
    this->_ip.clear();
    this->_method.clear();
    this->_filename.clear();
    this->_url.clear();
}

const std::string& Request::getClientIP(void) const
{
    return (_ip);
}

void Request::setClientIP(const std::string &clientIP)
{
    this->_ip = clientIP;
}

const std::string& Request::getMethod(void) const
{
    return (_method);
}

void Request::setMethod(const std::string &method)
{
    this->_method = method;
}

const std::string& Request::getProtocol(void) const
{
    return (_protocol);
}

void Request::setProtocol(const std::string &protocol)
{
    this->_protocol = protocol;
}

const std::string& Request::getFilename(void) const
{
    return (_filename);
}

void Request::setFilename(const std::string &filename)
{
    this->_filename = filename;
}

const std::string* Request::getArgument(const std::string &name) const
{
    return this->getValueFromMap(name, this->_Param_value);
}

std::vector<std::string> Request::getArgumentsKeys(void) const
{
    return this->mapToVector(this->_Param_value);
}

void Request::setArgument(const std::string &key, const std::string &value)
{
    this->setValueInMap(key, value, this->_Param_value);
}

const std::string& Request::getURL(void) const
{
    return (_url);
}

void Request::setURL(const std::string &url)
{
    this->_url = url;
}

const std::string* Request::getHeader(const std::string &key) const
{
    return this->getValueFromMap(key, this->_Header_value);
}

std::vector<std::string> Request::getHeaderKeys(void) const
{
    return this->mapToVector(this->_Header_value);
}

void Request::setHeader(const std::string &key, const std::string &value)
{
    this->setValueInMap(key, value, this->_Header_value);
}

const std::vector<char>* Request::getBody(void) const
{
    return (_body);
}

void Request::setBody(const std::vector<char> &body)
{
    if (this->_body == nullptr)
        this->_body = new std::vector<char>;

    *this->_body = body;
}

std::vector<std::string> Request::mapToVector(const std::unordered_map<std::string, std::string> &map) const
{
    std::vector<std::string> ret(map.size());
    size_t index = 0;

    for (const auto &[key, _] : map)
        ret[index++] = key;

    return ret;
}

const std::string *Request::getValueFromMap(const std::string &key, const std::unordered_map<std::string, std::string> &map) const
{
    auto it = map.find(key);

    if (it == map.end())
        return nullptr;

    return &(*it).second;
}

void Request::setValueInMap(
    const std::string &key,
    const std::string &value,
    std::unordered_map<std::string, std::string> &map
) {
    auto it = map.find(key);

    if (it == map.end())
        map.insert({
            key,
            value
        });
    else
        it->second = value;
}