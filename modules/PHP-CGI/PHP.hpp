#pragma once

#include "Zia.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <boost/process.hpp>
#include <mutex>

class PHP : public Zia::Module::IHandler {
    public:
        PHP(const std::string &path);
        ~PHP();
        void handle(const Zia::IRequest &req, Zia::IResponse &res, Zia::IContext &ctx, Zia::ILogger &log);

    private:
        bool isPHP(const std::string &str);
        void ExecPhpCgi(const Zia::IRequest &req, Zia::IResponse &res);
        boost::process::environment VarEnvPhp(const Zia::IRequest &req);
        //std::string extractFilename(const std::string pathname);
        std::string extractFilename(const std::string pathname);
        std::string getQuery(const std::string url);
        boost::process::environment _varEnv;
        std::string _pathname;
        std::vector<char> _body;
        std::string _scriptName;
        std::string _query;
        std::mutex _mutex;
};



extern "C" {

ZIA_EXPORT_SYMBOL Zia::Module::IHandler* createHandler(Zia::IConf &conf) {
    std::string path = "";
    auto obj = conf.read();

    if (obj->getString("path") != std::nullopt)
        path =  obj->getString("path").value();

    return (new PHP(path));
}

}