#pragma once

#include "globals.hpp"
#include "JniParam.hpp"

namespace jni {
    

    using JavaMethod = struct MethodInvoke*;
    using JavaObject = struct ObjectInvoke*;

    lib_api Param& GetFieldValue(JavaObject object, const char* name, JavaType exceptType);
    lib_api bool SetFieldValue(JavaObject object, const char* name, const Param& value);
}