#include "typedesc.hpp"
#include "../utils.hpp"

ObjRef TypeDesc::_type_desc_type_desc = new TypeDesc("TypeDesc", Object::_object_type_desc);

TypeDesc::TypeDesc(const std::string& name, ObjRef parent) : name(name), _parent(parent)
{}

TypeDesc& TypeDesc::bind_static(Name name, ObjRef object)
{
    _statics.emplace(name, object);
    return *this;
}

TypeDesc& TypeDesc::bind_member(Name name, size_t index)
{
    _members.emplace(name, index);
    return *this;
}

ObjRef& TypeDesc::get_static(const Name& name)
{
    auto it = _statics.find(name);
    if (it != _statics.end())
        return it->second;
    
    if (_parent)
        return _parent.get_as<TypeDesc>()->get_static(name);
        
    throw std::runtime_error(fmt("Static member '", name.get_name(), "' is not defined for type '", this->name, "'."));
}

ObjRef& TypeDesc::get_member(const Name& name, Object& object)
{
    auto it = _members.find(name);
    if (it != _members.end())
        return object.get_member(it->second);
    
    if (_parent)
        return _parent.get_as<TypeDesc>()->get_member(name, object);
    
    throw std::runtime_error(fmt("Member '", name.get_name(), "' is not defined for type '", this->name, "'."));
}

ObjRef TypeDesc::get_type_desc()
{
    return _type_desc_type_desc;
}