#include "function.hpp"
#include <iostream>
#include "object.hpp"
#include "typedesc.hpp"

int main()
{
    ObjRef x = new Object();

    std::cout << "x type: " << x->get_type_desc().get_as<TypeDesc>()->name << '\n';
    std::cout << "x type's type: " << x->get_type_desc().get_as<TypeDesc>()->get_type_desc().get_as<TypeDesc>()->name << '\n';
}