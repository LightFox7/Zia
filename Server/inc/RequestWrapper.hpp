#pragma once

#include <optional>

#include "ZiaTypes.hpp"

class RequestWrapper
{
    public:
        using ptr = std::shared_ptr<RequestWrapper>;

        RequestWrapper() = default;
        ~RequestWrapper() = default;

        void wrap(const Zia::IRequest &request);

        std::optional<Zia::RequestRef> unwrap();

        static ptr create();

    private:
        std::optional<Zia::RequestRef> _requestRef;
};