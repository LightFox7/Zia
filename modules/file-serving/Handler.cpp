#include <iostream>
#include <boost/filesystem.hpp>
#include <fstream>

#include "Handler.hpp"

Handler::Handler(Zia::IConf &conf)
{
    std::cout << "FILE SERVING CONSTRUCTOR" << std::endl;
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
    (void)ctx;
    if (res.getBody() != nullptr)
        return;
    if ((req.getMethod() != "GET" && req.getMethod() != "HEAD") || !this->_directory)
        return;

    std::string filename(req.getFilename());

    if (filename.empty() || filename == "/")
        filename = "/index.html";

    std::string filepath = this->_directory.value() + filename;

    if (!boost::filesystem::exists(filepath) || !boost::filesystem::is_regular_file(filepath)) {

        res.setCode(404);

    } else {
        std::ifstream is(filepath);

        std::string strBody(
            (std::istreambuf_iterator<char>(is)),
            (std::istreambuf_iterator<char>())
        );

        std::string mimeType = "";
        std::string value = "text/plain";
        std::string file = filename;
        size_t pos = 0;

        if ((pos = file.find_last_of('.')) != std::string::npos) {
            mimeType = file.substr(pos);
            value = this->extToMimeType(mimeType);
        }
        value += "; charset=utf-8";

        res.setBody(std::vector<char>(strBody.begin(), strBody.end()));
        res.setHeader("Content-Type", value);

        log.log("GET " + req.getFilename() + "\n");

    }
}

extern "C" {

ZIA_EXPORT_SYMBOL Zia::Module::IHandler* createHandler(Zia::IConf &conf)
{
    return (new Handler(conf));
}

}