#pragma once

#include <thread>

#include "Modules.hpp"

template <typename T>
class ZiaInstance
{
    public:
        ZiaInstance(Modules::ptr &modules, uint16_t port, const std::string &instanceName)
        :   _modules(modules),
            _port(port),
            _instanceName(instanceName),
            _isRunning(false),
            _hasError(false)
        {};

        ~ZiaInstance()
        {
            this->join();
        }

        void run()
        {
            this->_hasError = false;

            this->_th = std::thread([this]() {
                try {
                    T(this->_modules, this->_port).run();
                } catch (const std::exception &error) {
                    std::cerr << "Error : instance " << this->_instanceName << " : " << error.what() << std::endl;
                    std::cerr << this->_instanceName << " crashed." << std::endl;
                    std::cerr << "Type start_" << this->_instanceName << " to restart instance." << std::endl;

                    this->_hasError = true;
                }
            });

            std::cerr << "Instance " << this->_instanceName << " started." << std::endl;

            this->_isRunning = true;
        };

        bool isRunning() const
        {
            return this->_isRunning;
        }

        bool hasError() const
        {
            return this->_hasError;
        }

        void join()
        {
            if (!this->_isRunning)
                return;

            this->_isRunning = false;
            this->_th.join();
        }

    private:
        Modules::ptr _modules;
        uint16_t _port;
        std::string _instanceName;
        std::atomic_bool _isRunning;
        std::atomic_bool _hasError;
        std::thread _th;
};