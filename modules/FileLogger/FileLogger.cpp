/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-ugo.levi-cescutti
** File description:
** FileLogger
*/

#include "FileLogger.hpp"

FileLogger::FileLogger(std::string const &path) : _path(path)
{
}

FileLogger::~FileLogger()
{
}

void FileLogger::log(const std::string &str)
{
    std::ofstream outfile;

    outfile.open(_path, std::ios_base::app);
    outfile << str; 
    outfile.close();
}