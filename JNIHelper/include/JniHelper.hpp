#pragma once

#include "globals.hpp"
#include <initializer_list>
#include <stdio.h>

namespace jni {

    enum MessageLevel {
        DebugMsg, WarnMsg
    };

    using JNIHelperErrorFunc = void(*)(const char*, bool);
    using JNIMessageFunc     = void(*)(const char*, MessageLevel);
    using Helper = struct JniHelper*;

    lib_api Helper createHelper();
    lib_api void BindCallback(Helper helper, JNIHelperErrorFunc func);
}