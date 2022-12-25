#pragma once

#include <limits>
#include <string>
#include <unordered_set>

class Name
{
private:
    static std::unordered_set<std::string> _names;
    const char* _name;

public:
    explicit Name(const std::string& name);

    bool operator==(const Name& other) const;

    uintptr_t get_id() const;
    std::string get_name() const;
};

template <>
class std::hash<Name>
{
public:
    size_t operator()(const Name& name) const
    {
        return (size_t)name.get_id();
    }
};