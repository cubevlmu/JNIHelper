#pragma once

#include "JniHelper.hpp"
#include <jni.h>

namespace jni {

    struct JniHelper {
        JNIEnv* env;
        JNIHelperErrorFunc error;
        JNIMessageFunc msg;
    };

}