#pragma once

#include "code.hpp"
#include "name.hpp"
#include <string>
#include <unordered_map>

class TypeDesc : public Object
{
private:
    ObjRef _parent;
    std::unordered_map<Name, ObjRef> _statics;
    std::unordered_map<Name, size_t> _members;

protected:
    static ObjRef _type_desc_type_desc;

public:
    const std::string name;

    explicit TypeDesc(const std::string& name, ObjRef parent);

    TypeDesc& bind_static(Name name, ObjRef object);
    TypeDesc& bind_member(Name name, size_t index);

    ObjRef& get_static(const Name& name);
    ObjRef& get_member(const Name& name, Object& object);

    ObjRef get_type_desc() override;
};