#include "RequestWrapper.hpp"

RequestWrapper::ptr RequestWrapper::create()
{
    return std::make_shared<RequestWrapper>();
}

void RequestWrapper::wrap(const Zia::IRequest &request)
{
    this->_requestRef.emplace(std::cref(request));
}

std::optional<Zia::RequestRef> RequestWrapper::unwrap()
{
    if (!this->_requestRef)
        return {};

    auto request = this->_requestRef.value();

    this->_requestRef.reset();

    return std::optional<Zia::RequestRef>{request};
}