#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

class ObjRef;

class Object
{
private:
    friend class ObjRef;

    uintptr_t _ref_count = 0;

    void _add_ref();
    void _del_ref();

protected:
    static ObjRef _object_type_desc;
    
public:
    Object();
    virtual ~Object();

    virtual ObjRef get_type_desc();
    virtual ObjRef& get_member(size_t index);
    virtual ObjRef call();
};

class ObjRef
{
private:
    Object* _object = nullptr;

public:
    ObjRef();
    ObjRef(Object* object);
    ObjRef(const ObjRef& other);
    ObjRef(ObjRef&& other);
    ~ObjRef();

    operator bool();

    void reset();
    void operator=(Object* other);
    void operator=(const ObjRef& other);
    void operator=(ObjRef&& other);

    Object& operator*();
    Object* operator->();
    Object* get();

    // Use only if certain of underlying Object's type.
    template <typename T>
    requires std::is_base_of_v<Object, std::remove_cvref_t<T>>
    auto get_as()
    {
        return static_cast<std::remove_cvref_t<T>*>(_object);
    }
};