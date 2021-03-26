#include <iostream>

#include "DefaultLogger.hpp"

void DefaultLogger::log(const std::string &str)
{
    std::clog << str << std::endl;
}

Zia::LoggerPtr DefaultLogger::create()
{
    return std::make_unique<DefaultLogger>();
}