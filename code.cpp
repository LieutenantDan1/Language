#include "code.hpp"
#include <stdexcept>
#include "typedesc.hpp"
#include "utils.hpp"

Expression::Expression() {}

Expression::~Expression() {}

ObjRef Expression::evaluate()
{
    throw std::runtime_error("Expression: Cannot evaluate base expression.");
}

ObjRef Expression::assign(const ObjRef& value)
{
    throw std::runtime_error("This type of expression is not assignable.");
}

StaticVar::StaticVar(ObjRef& var) : _var(var)
{}

ObjRef StaticVar::evaluate()
{
    return var;
}

ObjRef StaticVar::assign(ObjRef& value)
{
    _var = value;
    return _var;
}

MemberAccess::MemberAccess(ExprPtr&& left, size_t index) : _left(std::forward<ExprPtr>(left)), _index(index)
{}

ObjRef MemberAccess::evaluate()
{
    return _left->evaluate()->get_member(_index);
}

ObjRef MemberAccess::assign(ObjRef& value)
{
    ObjRef& member = _left->evaluate()->get_member(_index);
    member = value;
    return member;
}

DynamicMemberAccess::DynamicMemberAccess(ExprPtr&& left, Name name) : _left(std::forward<ExprPtr>(left)), _name(name)
{}

ObjRef DynamicMemberAccess::evaluate()
{
    ObjRef left = _left->evaluate();
    return left->get_type_desc().get_as<TypeDesc>()->get_member(_name, *left);
}

ObjRef DynamicMemberAccess::assign(ObjRef& value)
{
    ObjRef left = _left->evaluate();
    ObjRef& member = left->get_type_desc().get_as<TypeDesc>()->get_member(_name, *left);
    member = value;
    return member;
}

ReferenceAssignment::ReferenceAssignment(ExprPtr&& left, ExprPtr&& right) : _left(std::forward<ExprPtr>(left)), _right(std::forward<ExprPtr>(right))
{}

ObjRef ReferenceAssignment::evaluate()
{
    _left->assign(_right->evaluate());
}

Call::Call(ExprPtr&& left) : _left(std::forward<ExprPtr>(left))
{}

ObjRef Call::evaluate()
{
    return _left->evaluate()->call(_right->evaluate());
}