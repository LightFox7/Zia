/*
** EPITECH PROJECT, 2020
** ZIA
** File description:
** Templated classe loading dynamic lib
*/

#pragma once

#include <memory>
#include <iostream>
#include <cstring>
#include <string>

#if __linux__
	#include <dlfcn.h>
	#include <experimental/filesystem>
#else
	#include <windows.h>
#endif

#include "ZiaTypes.hpp"

template <typename T>
class DynamicLib {

	private:
		std::shared_ptr<T> _module;
		void *_lib;

		using fptr_t = T *(*)(Zia::IConf &);

	public:

		DynamicLib(const std::string &path, const std::string &funcName, Zia::IConf &conf)
		{
			#if __linux__
				_lib = dlopen(path.c_str(), RTLD_LAZY | RTLD_NODELETE);
				if (!_lib)
    				fprintf(stderr, "dlopen failed: %s\n", dlerror());
				fptr_t fptr = (fptr_t)dlsym(_lib, funcName.c_str());
			#elif _WIN32
				HMODULE m = LoadLibrary(path.c_str());
				fptr_t fptr = (fptr_t)GetProcAddress(m, funcName.c_str());
			#endif
			if (!fptr) {
				std::cerr << "Warning, fptr is Null" << std::endl;
				_module = nullptr;
				return;
			}
			_module = std::shared_ptr<T>(fptr(conf));
			if (!_module)
				std::cerr << "Warning, Module lib is Null" << std::endl;
		}

		std::shared_ptr<T> GetDLib() const
		{
			return (_module);
		}

		~DynamicLib()
		{
			#if __linux__
				if (_lib == nullptr) {
					std::cerr << "Warning, Dynamic lib is Null" << std::endl;
				} else
					dlclose(_lib); // CLOSE LIB
			#endif
		}
};

/* example:

	TDynamicLib<IModule> dLibTest("/home/abenard/AA_epitech/tek3/dynamic lib/cmake so/build/libModule1.so", "ExportModule1");

    std::shared_ptr<IModule> lul = dLibTest.GetDLib();
    lul.get()->getId();
*/