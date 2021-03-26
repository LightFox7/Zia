/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** so
*/

#include <any>
#include "DynamicLib.hpp"

int main(void)
{
    DynamicLib<IModule> dLibTest("/home/abenard/AA_epitech/tek3/dynamic lib/cmake so/build/libModule1.so", "ExportModule1");

    std::shared_ptr<IModule> lul = dLibTest.GetDLib();
    lul.get()->getId();
    while(1);
    return 0;
}