#include <algorithm>
#include <sstream>
#include <boost/filesystem.hpp>
#include <fstream>
#include <streambuf>
#include <iostream>

#include "Handler.hpp"

static const std::vector<size_t> errorStatusCode{
    400,
    401,
    403,
    404,
    500,
    501,
    502,
    503,
    520,
    521,
    533
};

Handler::Handler(Zia::IConf &conf)
{
    std::cout << "ERROR PAGE CONSTRUCTOR" << std::endl;
    auto json = conf.read();

    if (!json)
        return;

    this->_directory = json->getString(DIRECTORY_KEY);
}

void Handler::handle(
            const Zia::IRequest &req,
            Zia::IResponse      &res,
            Zia::IContext       &ctx,
            Zia::ILogger        &log
)
{
    (void)req;
    (void)ctx;
    (void)log;
    if (!this->_directory)
        return;

    size_t statusCode = res.getCode();

    if (std::find(errorStatusCode.begin(), errorStatusCode.end(), statusCode) == errorStatusCode.end())
        return;

    std::string htmlPage = this->getHtmlPageFromStatusCode(statusCode);

    std::string filePath = this->_directory.value() + "/" + htmlPage;

    if (!boost::filesystem::exists(filePath) || !boost::filesystem::is_regular_file(filePath))
        return;

    std::ifstream file(filePath);

    std::string strBody(
        (std::istreambuf_iterator<char>(file)),
        (std::istreambuf_iterator<char>())
    );

    res.setBody(std::vector<char>(strBody.begin(), strBody.end()));
    res.setHeader("Content-Type", "text/html; charset=UTF-8");
}

std::string Handler::getHtmlPageFromStatusCode(size_t statusCode)
{
    std::stringstream htmlPage;

    htmlPage << "HTTP" << std::to_string(statusCode) << ".html";

    return htmlPage.str();
}

extern "C" {

ZIA_EXPORT_SYMBOL Zia::Module::IHandler* createHandler(Zia::IConf &conf)
{
    return (new Handler(conf));
}

}