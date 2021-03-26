/*
** EPITECH PROJECT, 2020
** zia
** File description:
** Handler1
*/

#include "PHP.hpp"
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

PHP::PHP(const std::string &path)
{
    _pathname = path;
}

bool PHP::isPHP(const std::string &str)
{
    if (str.find(".php") != std::string::npos)
        return (true);
    return (false);
}

void PHP::handle(const Zia::IRequest &req, Zia::IResponse &res, Zia::IContext &ctx, Zia::ILogger &log)
{
    std::unique_lock<std::mutex> lock(this->_mutex);

    int code = 0;
    (void)ctx;
    (void)log;
    if (isPHP(req.getFilename()) == false)
        return;
    _varEnv = VarEnvPhp(req);

    ExecPhpCgi(req, res);
    res.setHeader("Content-Type", "text/html; charset=UTF-8");

    this->_varEnv.clear();
    this->_body.clear();
    this->_scriptName.clear();
    this->_query.clear();
}

std::string PHP::extractFilename(const std::string pathname)
{
    size_t pos = 0;

    pos = pathname.find_last_of('/');
    if (pos != std::string::npos)
        return (pathname.substr(pos + 1));
    return (pathname);
}

std::string PHP::getQuery(const std::string url)
{
    size_t pos = 0;

    pos = url.find_first_of('?');
    if (pos != std::string::npos)
        return url.substr(pos + 1);
    return ("");
}

boost::process::environment PHP::VarEnvPhp(const Zia::IRequest &req)
{
    boost::process::environment varEnv = boost::this_process::environment();
    std::vector<std::string> headersKey = req.getHeaderKeys();
    std::string scriptName = extractFilename(req.getFilename());
    std::string pathInfo(boost::filesystem::current_path().string());
    std::string query = getQuery(req.getURL());

    varEnv["DOCUMENT_ROOT"] = pathInfo + "/www";
	varEnv["GATEWAY_INTERFACE"] = "CGI/1.1";
    varEnv["HOME"] = getenv("HOME");
    varEnv["PATH"] = std::getenv("PATH");
    varEnv["PATH_INFO"] = req.getURL();
    varEnv["PATH_TRANSLATED"] = pathInfo;
    varEnv["QUERY_STRING"] = query;
    varEnv["REQUEST_URI"] = req.getURL();
    varEnv["REQUEST_METHOD"] = req.getMethod().data();
    varEnv["REMOTE_ADDR"] = req.getClientIP().data();
    varEnv["SCRIPT_FILENAME"] = scriptName;
    varEnv["SCRIPT_NAME"] = "mdr.php";
    varEnv["SERVER_NAME"] = "zia";
    varEnv["SERVER_PORT"] = "8080";
    varEnv["SERVER_PROTOCOL"] = req.getProtocol().data();
    varEnv["REDIRECT_STATUS"] = "true";
    if (req.getBody()) {
        varEnv["CONTENT_LENGTH"] = std::to_string(req.getBody()->size());
        auto contentType = req.getHeader("content-type");
        if (contentType)
            varEnv["CONTENT_TYPE"] = *contentType;
    }

    for (auto it : headersKey) {
        if (it == "Accept")
            varEnv["HTTP_ACCEPT"] = req.getHeader("Accept")->data();
        if (it == "Accept-Encoding")
            varEnv["HTTP_ACCEPT_ENCODING"] = req.getHeader("Accept-Encoding")->data();
        if (it == "Accept-Charset")
            varEnv["HTTP_ACCEPT_CHARSET"] = req.getHeader("Accept-Charset")->data();
        if (it == "Accept-Language")
            varEnv["HTTP_ACCEPT_LANGUAGE"] = req.getHeader("Accept-Language")->data();
    }
    _scriptName = scriptName;
    _query = query;
    return varEnv;
}

void PHP::ExecPhpCgi(const Zia::IRequest &req, Zia::IResponse &res)
{
    if (!boost::filesystem::exists(_pathname)) {
        res.setCode(500);
        return;
    }
    int result = 0;
    boost::process::opstream pipeIn;
    boost::process::ipstream pipeOut;
    std::string line = "";
    std::vector<char> tmpBody;
    size_t pos = 0;
    bool isbody = false;
    bool isstatus = false;

    boost::process::child c(_pathname, boost::process::std_out > pipeOut, boost::process::std_in < pipeIn, _varEnv);

    if (req.getBody()) {
        for (const auto &it : *req.getBody()) {
            pipeIn << it;
        }
    }

    pipeIn.flush();

    while (c.running() && std::getline(pipeOut, line)) {
        if (!line.empty() && line[0] == '\r')
            isbody = true;
        if (!line.empty() && line[0] != '\r' && isbody == false) {
            pos = line.find(':');
            if (pos != std::string::npos && line.substr(0, pos) == "Status") {
                isstatus = true;
                res.setCode(std::stoi(line.substr(pos + 2, 3)));
            } else if (pos != std::string::npos)
                res.setHeader(line.substr(0, pos), line.substr(pos + 2));
        }
        if (!line.empty() && isbody == true)
            for (size_t idx = 0; line[idx]; idx++)
                tmpBody.push_back(line[idx]);
    }
    c.wait();
    pipeIn.pipe().close();
    pipeOut.pipe().close();
    result = c.exit_code();
    res.setBody(tmpBody);
    if (isstatus == false)
        res.setCode(200);
}

PHP::~PHP()
{

}