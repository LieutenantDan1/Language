#pragma once

#include "../Runtime/code.hpp"
#include "object.hpp"
#include <vector>

class Function : public Object
{
private:
    ExprPtr _body;
    std::vector<ObjRef*> _params;

protected:
    static ObjRef _function_type_desc;

public:
    explicit Function(ExprPtr&& body);

    ObjRef get_type_desc() override;

    ObjRef call() override;
};