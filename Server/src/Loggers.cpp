 
#include "Loggers.hpp"

Loggers::Loggers(std::vector<Zia::LoggerPtr> loggers)
{
    _loggers = loggers;
}

void Loggers::log(const std::string &str)
{
    for (auto &logger : _loggers)
        logger->log(str);
}