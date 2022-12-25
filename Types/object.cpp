#include "object.hpp"
#include <stdexcept>
#include "typedesc.hpp"
#include "../utils.hpp"

ObjRef Object::_object_type_desc = new TypeDesc("Object", nullptr);

void Object::_add_ref()
{
    ++_ref_count;
}

void Object::_del_ref()
{
    if (--_ref_count == 0)
        delete this;
}

Object::Object() {}

Object::~Object() {}

ObjRef Object::get_type_desc()
{
    return _object_type_desc;
}

ObjRef& Object::get_member(size_t index)
{
    throw std::runtime_error(fmt("Object of type '", this->get_type_desc().get_as<TypeDesc>()->name, "' has no members."));
}

ObjRef Object::call()
{
    throw std::runtime_error(fmt("Object of type '", this->get_type_desc().get_as<TypeDesc>()->name, "' is not callable."));
}

ObjRef::ObjRef() {}

ObjRef::ObjRef(Object* object) : _object(object)
{
    if (_object != nullptr)
        _object->_add_ref();
}

ObjRef::ObjRef(const ObjRef& other) : _object(other._object)
{
    if (_object != nullptr)
        _object->_add_ref();
}

ObjRef::ObjRef(ObjRef&& other) : _object(other._object)
{
    other._object = nullptr;
}

ObjRef::~ObjRef()
{
    if (_object != nullptr)
        _object->_del_ref();
}

ObjRef::operator bool()
{
    return _object != nullptr;
}

void ObjRef::reset()
{
    if (_object != nullptr)
        _object->_del_ref();
    _object = nullptr;
}

void ObjRef::operator=(Object* other)
{
    if (_object != nullptr)
        _object->_del_ref();
    _object = other;
    if (_object != nullptr)
        _object->_add_ref();
}

void ObjRef::operator=(const ObjRef& other)
{
    if (_object != nullptr)
        _object->_del_ref();
    _object = other._object;
    if (_object != nullptr)
        _object->_add_ref();
}

void ObjRef::operator=(ObjRef&& other)
{
    if (_object != nullptr)
        _object->_del_ref();
    _object = other._object;
    other._object = nullptr;
}

Object& ObjRef::operator*()
{
    if (_object == nullptr)
        throw std::runtime_error("Cannot dereference null object.");
    return *_object;
}

Object* ObjRef::operator->()
{
    if (_object == nullptr)
        throw std::runtime_error("Cannot dereference null object.");
    return _object;
}

Object* ObjRef::get()
{
    return _object;
}