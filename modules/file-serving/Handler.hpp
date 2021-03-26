#pragma once

#include "Zia.hpp"

#define DIRECTORY_KEY "directory"

class Handler : public Zia::Module::IHandler
{
    public:
        Handler(Zia::IConf &conf);
        ~Handler() = default;

        void handle(
            const Zia::IRequest &req,
            Zia::IResponse      &res,
            Zia::IContext       &ctx,
            Zia::ILogger        &log
        );

    private:
        std::optional<std::string> _directory;
        static const std::string &extToMimeType(const std::string &ext);
};