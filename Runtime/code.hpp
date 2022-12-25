#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include "name.hpp"
#include "../Types/object.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class Expression
{
protected:

public:
    Expression();
    virtual ~Expression();

    virtual ObjRef evaluate();
    virtual ObjRef assign(ObjRef& value);
};
using ExprPtr = std::unique_ptr<Expression>;

class StaticVar : public Expression
{
private:
    ObjRef& _var;

public:
    explicit StaticVar(ObjRef& var);

    ObjRef evaluate() override;
    ObjRef assign(ObjRef& value) override;
};

class MemberAccess : public Expression
{
private:
    ExprPtr _left;
    size_t _index;

public:
    MemberAccess(ExprPtr&& left, size_t index);

    ObjRef evaluate() override;
    ObjRef assign(ObjRef& value) override;
};

class DynamicMemberAccess : public Expression
{
private:
    ExprPtr _left;
    Name _name;

public:
    DynamicMemberAccess(ExprPtr&& left, Name name);

    ObjRef evaluate() override;
    ObjRef assign(ObjRef& value) override;
};

class ReferenceAssignment : public Expression
{
private:
    ExprPtr _left;
    ExprPtr _right;

public:
    ReferenceAssignment(ExprPtr&& left, ExprPtr&& right);

    ObjRef evaluate() override;
};

class Call : public Expression
{
private:
    ExprPtr _left;
    std::vector<std::pair<ObjRef*, ExprPtr>> _args;

public:
    explicit Call(ExprPtr&& left);

    ObjRef evaluate() override;
};