#include "Context.hpp"

const std::any *Context::get(const std::string &key) const
{
    auto it = this->_context.find(key);

    if (it == this->_context.end())
        return nullptr;

    return &(*it).second;
}

void Context::set(const std::string &key, const std::any &value)
{
    auto it = this->_context.find(key);

    if (it == this->_context.end())
        this->_context.insert({
            key,
            value
        });
    else
        it->second = value;
}