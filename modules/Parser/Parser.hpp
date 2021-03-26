#pragma once

#include "Zia.hpp"
#include "Request.hpp"

class Parser : public Zia::Module::IParser {

    public:
        Parser();
        std::unique_ptr<IInstance> create(Zia::IInput &input, Zia::ILogger &log, Zia::IRequest::IEmitter &requestEmitter);

    class Instance : public IInstance {

        public:
            Instance(Zia::IInput &input, Zia::ILogger &log, Zia::IRequest::IEmitter &requestEmitter);
            void parse(void);
            bool is_request_line(std::string &line);
            void parse_method(std::string &line, Request &requete);
            void parseHeader(std::string &line, Request &requete);

        private:
            Zia::IInput &_input;
            Zia::ILogger &_logger;
            Zia::IRequest::IEmitter &_emitter;
            Request _currentRequest;

            void internalParse();
    };
};



extern "C" {

ZIA_EXPORT_SYMBOL Zia::Module::IParser* createParser(Zia::IConf &conf)
{
    (void)conf;
    return (new Parser());
}

}