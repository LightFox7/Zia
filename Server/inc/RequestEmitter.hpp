#pragma once

#include "ZiaTypes.hpp"
#include "RequestWrapper.hpp"

class RequestEmitter : public Zia::IRequest::IEmitter
{
    public:
        RequestEmitter(const RequestWrapper::ptr &requestWrapper);
        ~RequestEmitter() = default;

        void emit(const Zia::IRequest &request);

        static Zia::RequestEmitterPtr create(const RequestWrapper::ptr &requestWrapper);

    private:
        RequestWrapper::ptr _requestWrapper;
};