#pragma once 

#include <jni.h>
#include "JniParam.hpp"

namespace jni {

    struct JavaFieldInvoke
    {
        jclass clazz;
        jobject instance;
        jfieldID fid;
        const char* name;
        const char* sig;
        bool isStatic;
        JavaType exceptType;
    };
    
}