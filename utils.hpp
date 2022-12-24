#pragma once

#include <sstream>
#include <string>

template <typename... Args>
std::string fmt(const Args&... args)
{
    std::stringstream s;
    (s << ... << args);
    return s.str();
}