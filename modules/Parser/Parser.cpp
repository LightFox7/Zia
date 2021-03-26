/*
** EPITECH PROJECT, 2020
** zia
** File description:
** Handler1
*/

#include "Parser.hpp"
#include "debug.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>

Parser::Parser()
{

}

std::unique_ptr<Parser::IInstance> Parser::create(Zia::IInput &input, Zia::ILogger &log, Zia::IRequest::IEmitter &requestEmitter)
{
    return std::make_unique<Parser::Instance>(input, log, requestEmitter);
}

Parser::Instance::Instance(Zia::IInput &input, Zia::ILogger &log, Zia::IRequest::IEmitter &requestEmitter) : _input(input), _logger(log), _emitter(requestEmitter)
{
}

const std::vector<std::string> _method = {
    "GET",
    "HEAD",
    "POST",
    "PUT",
    "DELETE",
    "CONNECT",
    "OPTIONS",
    "TRACE"
};

bool Parser::Instance::is_request_line(std::string &line)
{
    for (size_t i = 0; i < _method.size(); i++)
        if (line.find(_method[i]) != std::string::npos)
            return (true);
    return (false);
}

std::vector<std::string> splitByChar(std::string &line, char c)
{
    size_t pos = line.find(c);
    size_t idx = 0;
    std::vector<std::string> tab;

    while (pos != std::string::npos) {
        tab.push_back(line.substr(idx, pos - idx));
        idx = pos + 1;
        pos = line.find(c, idx);
    }
    tab.push_back(line.substr(idx, std::min(pos, line.size()) - idx + 1));
    return (tab);
}

std::vector<std::string> stringSplit(const std::string &str,
                                               const std::string &delim)
{
    std::vector<std::string> ret;
    size_t pos = 0;
    size_t count = 0;

    for (count = str.find(delim); count != std::string::npos; count = str.find(delim, pos)) {
        ret.push_back(str.substr(pos, count - pos));
        pos = count + 1;
    }
    ret.push_back(str.substr(pos, count - pos));
    return ret;
}

void Parser::Instance::parse_method(std::string &line, Request &requete)
{
    std::vector<std::string> split = stringSplit(line, " ");

    if (split.size() > 0 && is_request_line(split[0]))
        requete.setMethod(split[0]);
    if (split.size() > 1) {
        requete.setURL(split[1]);
        auto urlSplit = stringSplit(split[1], "?");
        if (!urlSplit.empty())
            requete.setFilename(urlSplit.front());
    }
    if (split.size() > 2)
        requete.setProtocol(split[2]);
}

void Parser::Instance::parseHeader(std::string &line, Request &requete)
{
    std::string key = "";
    std::string content = "";
    size_t pos = line.find(':');

    if (pos != std::string::npos) {
        key = line.substr(0, pos);
        if (line.size() > pos + 2)
            content = line.substr(pos + 2);
        // HTTP headers name are case insensitive
        boost::algorithm::to_lower(key);
        requete.setHeader(key, content);
    }
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void Parser::Instance::parse(void)
{
    try {
        this->internalParse();
    } catch (const std::exception &error) {
        std::cerr << "Invalid request : " << error.what() << "." << std::endl;
    }
}

void Parser::Instance::internalParse()
{
    char *data = new char[1];
    size_t bytes = 0;
    std::string request;
    std::string end_pattern("\r\n\r\n");
    std::string line;
    int length = 0;

    while ((bytes = _input.read(1, data)) > 0) {
        for (size_t i = 0; i < bytes; i++)
            request.push_back(data[i]);
        if (request.find(end_pattern) != std::string::npos)
            break;
    }
    if (request.size() <= 0)
        return;

    // We absolutely need to do this because _currentRequest attribute is passed to request emitter as reference.
    // Reference is then passed to RequestWrapper, which is used in client.Refresh(), after parse() call.
    // So the reference hold in RequestWrapper is every time the same reference on the _currentRequest attribute.
    // This is safe because one request at time is parsed and handled.
    this->_currentRequest.reset();

    std::istringstream iss(request);

    while (std::getline(iss, line)) {
        if(!line.empty() && *line.rbegin() == '\r')
            line = line.erase(line.size()-1, 1);
        if (is_request_line(line) == true)
            parse_method(line, this->_currentRequest);
        parseHeader(line, this->_currentRequest);
        if (line.compare(0, 15, "Content-Length:") == 0) {
            if (is_number(line.substr(16)) == true) {
                length = std::stoi(line.substr(16));
            } else
                length = 0;
        }
        if (length > 0) {
            char *body = new char[length];
            auto realBodyLenght = _input.read(length, body);
            this->_currentRequest.setBody(std::vector<char>(body, body + realBodyLenght));
            length = 0;
        }
    }
    if (this->_currentRequest.getMethod() != "")
        _emitter.emit(this->_currentRequest);
}