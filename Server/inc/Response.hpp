#include <unordered_map>

#include "Zia.hpp"

#define CRLF "\r\n"

class Response : public Zia::IResponse
{
    public:
        Response();
        ~Response();

        bool isPipelineAborted() const;
        void abortPipeline(void);

        size_t getCode(void) const;
        void setCode(size_t code);

        const std::string *getHeader(const std::string &key) const;
        void setHeader(const std::string &key, const std::string &value);

        const std::vector<char> *getBody(void) const;
        void setBody(const std::vector<char> &body);

        std::string serialize() const;

        static const std::string &getStatusCodeMessage(size_t code);

        void setNullBody();

    private:
        bool _isPipelineAborted;
        size_t _code;
        std::vector<char> *_body;
        std::unordered_map<std::string, std::string> _headers;
};