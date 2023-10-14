#include "_JNICaller.hpp"

#include "_JniCallbackHelper.hpp"
#include "_JniHelper.hpp"

namespace jni {

    inline static void callStatic(MethodInvoke* invoke, JNIEnv* env) {

        auto type = invoke->result->type;
        auto* result = invoke->result;

        auto* clazz = invoke->invoke->_class;
        auto* methodId = invoke->mid;
        auto* args = invoke->params;


        switch (type)
        {
        case JavaInt:    result->value.i = env->CallStaticIntMethodA(clazz, methodId, args);     break;
        case JavaDouble: result->value.d = env->CallStaticDoubleMethodA(clazz, methodId, args);  break;
        case JavaFloat:  result->value.f = env->CallStaticFloatMethodA(clazz, methodId, args);   break;
        case JavaBool:   result->value.b = env->CallStaticBooleanMethodA(clazz, methodId, args); break;
        case JavaChar:   result->value.c = env->CallStaticCharMethodA(clazz, methodId, args);    break;
        case JavaByte:   result->value.byte = env->CallStaticByteMethodA(clazz, methodId, args); break;
        case JavaLong:   result->value.l = env->CallStaticLongMethodA(clazz, methodId, args);    break;
        case JavaIntObject:
        case JavaStringObject:
        case JavaLongObject:
        case JavaDoubleObject:
        case JavaFloatObject:
        case JavaCharObject:
        case JavaByteObject:
        case JavaObjects: result->value.j = env->CallStaticObjectMethodA(clazz, methodId, args); break;
        case JavaByteArray: break;
        case JavaVoid:    env->CallStaticVoidMethodA(clazz, methodId, args); break;
        }
    }

    inline static void callDefault(MethodInvoke* invoke, JNIEnv* env) {

        auto type = invoke->result->type;
        auto* result = invoke->result;

        auto* clazzInstance = invoke->invoke->_instance;
        auto* methodId = invoke->mid;
        auto* args = invoke->params;


        switch (type)
        {
        case JavaInt:    result->value.i = env->CallIntMethodA(clazzInstance, methodId, args);     break;
        case JavaDouble: result->value.d = env->CallDoubleMethodA(clazzInstance, methodId, args);  break;
        case JavaFloat:  result->value.f = env->CallFloatMethodA(clazzInstance, methodId, args);   break;
        case JavaBool:   result->value.b = env->CallBooleanMethodA(clazzInstance, methodId, args); break;
        case JavaChar:   result->value.c = env->CallCharMethodA(clazzInstance, methodId, args);    break;
        case JavaByte:   result->value.byte = env->CallByteMethodA(clazzInstance, methodId, args); break;
        case JavaLong:   result->value.l = env->CallLongMethodA(clazzInstance, methodId, args);    break;
        case JavaIntObject:
        case JavaStringObject:
        case JavaLongObject:
        case JavaDoubleObject:
        case JavaFloatObject:
        case JavaCharObject:
        case JavaByteObject:
        case JavaObjects: result->value.j = env->CallObjectMethodA(clazzInstance, methodId, args); break;
        case JavaByteArray: break;
        case JavaVoid:    env->CallVoidMethodA(clazzInstance, methodId, args); break;
        }
    }

    void callMethod(Helper helper, JavaMethod mtd)
    {
        auto* env = helper->env;
        auto* invoke = mtd;

        if(invoke->invoke->isStatic) callStatic(invoke, env);
        else callDefault(invoke, env);
    }


}