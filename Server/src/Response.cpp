/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** Response
*/

#include <sstream>

#include "Response.hpp"
#include "HttpHeaders.hpp"

Response::Response() : _isPipelineAborted(false), _code(200), _body(nullptr)
{
}

Response::~Response()
{
    if (this->_body != nullptr)
        delete this->_body;
}

bool Response::isPipelineAborted() const
{
    return this->_isPipelineAborted;
}

void Response::abortPipeline(void)
{
    this->_isPipelineAborted = true;
}

size_t Response::getCode(void) const
{
    return (_code);
}

void Response::setCode(size_t code)
{
    if (code < 100 || code > 999)
        _code = 500;
    else
        _code = code;
}

const std::string* Response::getHeader(const std::string &key) const
{
    auto it = _headers.find(key);

    if (it == _headers.end())
        return nullptr;

    return &(*it).second;
}

void Response::setHeader(const std::string &key, const std::string &value)
{
    auto it = _headers.find(key);

    if (it == _headers.end())
        _headers.insert({
            key,
            value
        });
    else
        it->second = value;
}

const std::vector<char>* Response::getBody(void) const
{
    return (_body);
}

void Response::setBody(const std::vector<char> &body)
{
    if (_body == nullptr)
        _body = new std::vector<char>;

    *_body = body;

    this->setHeader(CONTENT_LENGTH, std::to_string(_body->size()));
}

void Response::setNullBody()
{
    if (this->_body == nullptr)
        return;

    delete this->_body;
    this->_body = nullptr;

    auto it = this->_headers.find(CONTENT_LENGTH);

    if (it == this->_headers.end())
        return;

    this->_headers.erase(it);
}

std::string Response::serialize(void) const
{
    std::stringstream ss;

    // HTTP/1.1 200 OK CRLF
    ss << "HTTP/1.1 " << this->_code << " " << getStatusCodeMessage(this->_code) << CRLF;

    // headerName: headerValue CRLF
    for (const auto &[headerName, headerValue] : this->_headers)
        ss << headerName << ": " << headerValue << CRLF;

    // http empty line
    ss << CRLF;

    if (this->_body == nullptr)
        return ss.str();

    for (const auto &it : *this->_body)
        ss << it;

    return ss.str();
}