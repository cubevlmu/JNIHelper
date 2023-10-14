#pragma once

#include "globals.hpp"
#include <initializer_list>
#include "JniParam.hpp"

namespace jni {

    using JavaMethod = struct MethodInvoke*;
    using JavaObject = struct ObjectInvoke*;

    using Helper = struct JniHelper*;

    lib_api bool Invoke(Helper helper, JavaMethod method);
    lib_api JavaMethod CreateInvoke(Helper helper, JavaObject clazz, JavaType returnType, const char* name, const char* signature, std::initializer_list<Param> params);
    lib_api void DestroyInvoke(Helper helper, JavaMethod mtd);
    lib_api Param* GetReturnValue(JavaMethod method);

    lib_api JavaObject FindStaticClass(Helper helper, const char* name);
    lib_api JavaObject CreateByJObj(Helper helper, const Param& param); //Replace jobject to Java

    lib_api void* CreateBooleanObject(Helper helper, const Param& param);
    lib_api void* CreateIntObject(Helper helper, const Param& param);
    lib_api void* CreateLongObject(Helper helper, const Param& param);
    lib_api void* CreateFloatObject(Helper helper, const Param& param);
    lib_api void* CreateDoubleObject(Helper helper, const Param& param);
    lib_api void* CreateCharObject(Helper helper, const Param& param);
    lib_api void* CreateByteObject(Helper helper, const Param& param);
    lib_api void* CreateStringObject(Helper helper, const Param& param);

    lib_api void DeleteObjectRef(Helper helper, void* p);
}