#include "_JniHelper.hpp"
#include "JniHelper.hpp"
#include "_JniCallbackHelper.hpp"

#include <jni.h>

namespace tool {

JNIEnv *myGlobalJNIEnv = nullptr;

}
namespace jni {

    static void handleErrToJavaStack(const char* msg, bool value) {

    }

    Helper createHelper() {
        static auto* helper = new JniHelper();
        helper->env = tool::myGlobalJNIEnv;
        helper->error = [](const char* msg, bool a) {
            std::cerr << "JNIHelper Error : " << msg << "\n";
        };
        helper->msg = [](const char* msg, MessageLevel lv) {
            if(lv == MessageLevel::DebugMsg) {
                std::cout << "JNIHelper Debug : " << msg << "\n";
            } else {
                std::cerr << "JNIHelper Warning : " << msg << "\n";
            }
        };
        return helper;
    }

    void BindCallback(Helper helper, JNIHelperErrorFunc func) {
        helper->error = func;
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
