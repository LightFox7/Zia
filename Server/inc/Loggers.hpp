
#include "ZiaTypes.hpp"

class Loggers : public Zia::ILogger
{

    public:
        Loggers(std::vector<Zia::LoggerPtr> loggers);
        void log(const std::string &str);

    private:
        std::vector<Zia::LoggerPtr> _loggers;
};