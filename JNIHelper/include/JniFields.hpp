#pragma once

#include "globals.hpp"
#include "JniParam.hpp"

namespace jni {
    
    using JavaMethod = struct MethodInvoke*;
    using JavaObject = struct ObjectInvoke*;
    using Helper = struct JniHelper*;
    using JavaField = struct JavaFieldInvoke*;

    lib_api JavaField CreateFieldInvoke(Helper helper, JavaObject object, JavaType exceptType, const char* name, const char* sig);

    lib_api Param* GetFieldValue(Helper helper, JavaField object);
    lib_api bool SetFieldValue(Helper helper, JavaField object, const Param& value);

    lib_api void DestroyFieldInvoke(Helper helper, JavaField f);
}