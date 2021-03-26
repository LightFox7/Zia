/*
** EPITECH PROJECT, 2021
** Request.hpp
** File description:
** Request.hpp
*/

#include <unordered_map>
#include <queue>

#include "Zia.hpp"

class Request : public Zia::IRequest {

    public:
        Request();
        ~Request();

        void reset();

        const std::string& getClientIP(void) const;
        void setClientIP(const std::string &clientIP);

        const std::string& getMethod(void) const override;
        void setMethod(const std::string &method);

        const std::string& getProtocol(void) const;
        void setProtocol(const std::string &protocol);

        const std::string& getFilename(void) const;
        void setFilename(const std::string &filename);

        const std::string* getArgument(const std::string &name) const;
        std::vector<std::string> getArgumentsKeys(void) const;
        void setArgument(const std::string &key, const std::string &value);


        const std::string& getURL(void) const;
        void setURL(const std::string &url);

        // HEADER

        const std::string* getHeader(const std::string &key) const;
        std::vector<std::string> getHeaderKeys(void) const;
        void setHeader(const std::string &key, const std::string &value);

        // BODY

        const std::vector<char>* getBody(void) const;
        void setBody(const std::vector<char> &body);

    private:
        std::vector<char>* _body;
        std::unordered_map<std::string, std::string> _Header_value;

        std::unordered_map<std::string, std::string> _Param_value;

        std::string _ip;
        std::string _method;
        std::string _protocol;
        std::string _filename;
        std::string _url;

        std::vector<std::string> mapToVector(const std::unordered_map<std::string, std::string> &map) const;
        const std::string *getValueFromMap(const std::string &key, const std::unordered_map<std::string, std::string> &map) const;
        void setValueInMap(const std::string &key, const std::string &value, std::unordered_map<std::string, std::string> &map);
};