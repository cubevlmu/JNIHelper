#include "_JniHelper.hpp"
#include "jni.h"
#include "JniHelper.hpp"


namespace tool {

JNIEnv *myGlobalJNIEnv = nullptr;

}
namespace jni {

    lib_api Helper createHelper() {
        auto* helper = new JniHelper();
        helper->env = tool::myGlobalJNIEnv;
        return helper;
    }

    lib_api void BindCallback(Helper helper, JNIHelperErrorFunc func) {
        if(func != nullptr) {
            helper->error = func;
        }
    }
    
} // namespace jni

lib_api jint __stdcall JNI_OnLoad(JavaVM *vm, void *reserved) {
    
    JNIEnv *env = nullptr;
    jint result = vm->GetEnv((void **)&env, JNI_VERSION_1_8);

    if (result == JNI_EDETACHED) {
        result = vm->AttachCurrentThread((void **)&env, nullptr);
        if (result != JNI_OK) {
            return -1; 
        }
        tool::myGlobalJNIEnv = env;
    } else if (result == JNI_OK) {
        tool::myGlobalJNIEnv = env;
    }

    return JNI_VERSION_1_8; 
}
