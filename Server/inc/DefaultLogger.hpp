#pragma once

#include "ZiaTypes.hpp"

class DefaultLogger : public Zia::Module::ILogger
{
    public:
        DefaultLogger() = default;
        ~DefaultLogger() = default;

        void log(const std::string &str);

        static Zia::LoggerPtr create();
};