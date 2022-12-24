#include "function.hpp"
#include "typedesc.hpp"

ObjRef Function::_function_type_desc(new TypeDesc("Function", Object::_object_type_desc));

Function::Function(ExprPtr&& body) : _body(std::forward<ExprPtr>(body))
{}

ObjRef Function::get_type_desc()
{
    return _function_type_desc;
}

ObjRef Function::call()
{
    
}