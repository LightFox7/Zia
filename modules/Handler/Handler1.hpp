#pragma once

#include "Zia.hpp"

class Handler1 : public Zia::Module::IHandler {
public:
    Handler1();
    ~Handler1();
    void handle(const Zia::IRequest &req, Zia::IResponse &res, Zia::IContext &ctx, Zia::ILogger &log);
};



extern "C" {

ZIA_EXPORT_SYMBOL Zia::Module::IHandler* createHandler(Zia::IConf &conf);

}