#include <unordered_map>

#include "Zia.hpp"

class Context : public Zia::IContext
{
    public:

        Context() = default;
        ~Context() = default;

        const std::any *get(const std::string &key) const;

        void set(const std::string &key, const std::any &value);

    private:
        std::unordered_map<std::string, std::any> _context;
};