/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** main
*/

#include <iostream>

#include "Terminal.hpp"
#include "ParseArgs.hpp"

int main(int ac, char **av)
{
    try {
        // parse args
        ParseArgs args(ac, av);

        // Init modules
        auto modules = Modules::create();

        // Start REPL
        Terminal(modules, args).run();

    } catch (const std::exception &err) {
        std::cerr << "Error : " << err.what() << "." << std::endl;
        return 84;
    }
    return 0;
}