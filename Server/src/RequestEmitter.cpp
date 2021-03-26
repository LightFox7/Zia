#include "RequestEmitter.hpp"
#include <iostream>

RequestEmitter::RequestEmitter(
    const RequestWrapper::ptr &requestWrapper
)
:   _requestWrapper(requestWrapper)
{}

void RequestEmitter::emit(const Zia::IRequest &request)
{
    this->_requestWrapper->wrap(request);
}

Zia::RequestEmitterPtr RequestEmitter::create(const RequestWrapper::ptr &requestWrapper)
{
    return std::make_shared<RequestEmitter>(requestWrapper);
}