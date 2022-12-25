#include <cstring>
#include "name.hpp"

Name::Name(const std::string& name)
{
    auto existing = _names.find(name);
    if (existing != _names.end())
        _name = existing->c_str();
    else
        _name = _names.insert(name).first->c_str();
}

bool Name::operator==(const Name& other) const
{
    // THIS WORKS IN THIS CASE
    return _name == other._name;
}

uintptr_t Name::get_id() const
{
    return reinterpret_cast<uintptr_t>(_name);
}

std::string Name::get_name() const
{
    return std::string(_name);
}

std::unordered_set<std::string> Name::_names{};