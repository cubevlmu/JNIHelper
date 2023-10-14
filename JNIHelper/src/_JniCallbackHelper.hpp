#include "JniCallbackHelper.hpp"

#include <jni.h>

namespace jni {

    struct ObjectInvoke {
        const char* name;
        jclass _class;
        jobject _instance;
        bool isStatic;
    };

    struct MethodInvoke {
        jvalue* params;
        ObjectInvoke* invoke;
        JavaType returnType;
        const char* name;
        jmethodID mid;
        Param* result;
        int parmsCount;
    };

    jvalue ParseToJValue(const Param& p);
    void* CreateRuntimeException(Helper helper, const char* msg);
}