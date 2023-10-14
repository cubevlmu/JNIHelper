#include "_JniCallbackHelper.hpp"

#include "_JniHelper.hpp"
#include "JniCallbackHelper.hpp"
#include "_JNICaller.hpp"

#include <jni.h>

namespace jni {

    bool Invoke(Helper helper, JavaMethod method) {
        callMethod(helper, method);
        return true;
    }

    JavaMethod CreateInvoke(Helper helper, JavaObject clazz, JavaType returnType, const char* name, const char* signature, std::initializer_list<Param> params) {
        auto* env = helper->env;

        jvalue* values = new jvalue[params.size()]();
        int index = 0;

        for (auto item : params) {
            auto result = ParseToJValue(item);
            values[index] = result;
            index++;
        }

        auto mid = clazz->isStatic ? env->GetStaticMethodID(clazz->_class, name, signature) : env->GetMethodID(clazz->_class, name, signature);

        //env->CallVoidMethodA(clazz->_instance, methodID, values);
        auto* invoke = new MethodInvoke();
        invoke->params = values;
        invoke->invoke = clazz;
        invoke->name = clazz->name;
        invoke->mid = mid;
        invoke->parmsCount = params.size();
        invoke->result = new Param(); invoke->result->type = returnType;

#ifdef HelperDebug
        std::cout << "Invode Info : \n"
            << "Params : " << invoke->params << "\n"
            << "Invoke : " << invoke->invoke << "\n"
            << "Name   : " << invoke->name << "\n"
            << "MId    : " << invoke->mid << "\n"
            << "Result : " << invoke->result->type << "\n";
#endif

        return invoke;
    }

    jvalue ParseToJValue(const Param& p)
    {
        jvalue value;
        switch (p.type)
        {
        case JavaInt:
            value.i = p.value.i; break;
        case JavaDouble:
            value.d = p.value.d; break;
        case JavaFloat:
            value.f = p.value.f; break;
        case JavaBool:
            value.b = p.value.b; break;
        case JavaChar:
            value.c = p.value.c; break;
        case JavaByte:
            value.b = p.value.b; break;
        case JavaLong:
            value.j = p.value.l; break;
        case JavaIntObject:
        case JavaStringObject:
        case JavaLongObject:
        case JavaDoubleObject:
        case JavaFloatObject:
        case JavaCharObject:
        case JavaByteObject:
        case JavaObjects:
            value.l = (jobject)p.value.j; break;
        case JavaByteArray:
            break;
        default:
            break;
        }
#ifdef HelperDebug
        std::cout << "Parse To Value : Type : " << p.type << "\n";
#endif
        return value;
    }

    void* CreateRuntimeException(Helper helper, const char* msg)
    {
        auto* env = helper->env;

        jclass runtimeExceptionClass = env->FindClass("java/lang/RuntimeException");

        if (runtimeExceptionClass != nullptr) {
            jmethodID ctor = env->GetMethodID(runtimeExceptionClass, "<init>", "(Ljava/lang/String;)V");
            jstring message = env->NewStringUTF(msg);
            jobject exceptionObj = env->NewObject(runtimeExceptionClass, ctor, message);

            return exceptionObj;
        }
        else {
            std::cerr << "RuntimeException class not found" << std::endl;
        }

        return nullptr;
    }

    void DestroyInvoke(Helper helper, JavaMethod mtd) {
        auto* env = helper->env;

        delete[] mtd->params;
        delete mtd->result;

        auto* ink = mtd->invoke;

        env->DeleteLocalRef(ink->_class);
        env->DeleteLocalRef(ink->_instance);

        delete mtd;
    }

    Param* GetReturnValue(JavaMethod method) {
        return method->result;
    }

    JavaObject FindStaticClass(Helper helper, const char* name) {
        auto* env = helper->env;
        jclass clazz = env->FindClass(name);
        if (clazz == nullptr) {
            helper->error("Can't Find The JavaClass", false);
            return nullptr;
        }

#ifdef HelperDebug
        std::cout << "FindStaticClass : Class : " << clazz << "\n";
#endif

        auto* ivk = new ObjectInvoke();
        ivk->isStatic = true;
        ivk->_class = clazz;
        ivk->_instance = nullptr;
        ivk->name = name;


        return ivk;
    }


    JavaObject CreateByJObj(Helper helper, const Param& param) {
        if (param.type != JavaType::JavaObjects) {
            helper->error("param's type is not JavaObject", false);
            return nullptr;
        }
        auto* jobj = (jobject)param.value.j;

        auto* env = helper->env;
        if (jobj == nullptr) {
            helper->error("this instance object is null", false);
            return nullptr;
        }
        auto* clazz = env->GetObjectClass(jobj);
        if (clazz == nullptr) {
            helper->error("can't find the class object", false);
            return nullptr;
        }

        auto* ivk = new ObjectInvoke();
        ivk->_class = clazz;
        ivk->_instance = jobj;
        ivk->name = "";
        return ivk;
    }

    void* CreateBooleanObject(Helper helper, const Param& param) {
        auto env = helper->env;

        jclass booleanClass = env->FindClass("java/lang/Boolean");
        jmethodID booleanConstructor = env->GetMethodID(booleanClass, "<init>", "(Z)V");
        jboolean value = param.value.b;
        jobject booleanObject = env->NewObject(booleanClass, booleanConstructor, value);

        return booleanObject;
    }

    void* CreateIntObject(Helper helper, const Param& param) {
        auto env = helper->env;

        jclass integerClass = env->FindClass("java/lang/Integer");
        jmethodID integerConstructor = env->GetMethodID(integerClass, "<init>", "(I)V");
        jobject integerObject = env->NewObject(integerClass, integerConstructor, param.value.i);
        return integerObject;
    }

    void* CreateLongObject(Helper helper, const Param& param) {
        auto env = helper->env;

        jclass longClass = env->FindClass("java/lang/Long");
        jmethodID longConstructor = env->GetMethodID(longClass, "<init>", "(J)V");
        jobject longObject = env->NewObject(longClass, longConstructor, param.value.l);

        return longObject;
    }


    void* CreateFloatObject(Helper helper, const Param& param) {
        auto env = helper->env;
        jclass floatClass = env->FindClass("java/lang/Float");
        jmethodID floatConstructor = env->GetMethodID(floatClass, "<init>", "(F)V");
        jobject floatObject = env->NewObject(floatClass, floatConstructor, param.value.f);
        return floatObject;
    }

    void* CreateDoubleObject(Helper helper, const Param& param) {
        auto env = helper->env;

        jclass doubleClass = env->FindClass("java/lang/Double");
        jmethodID doubleConstructor = env->GetMethodID(doubleClass, "<init>", "(D)V");
        jobject doubleObject = env->NewObject(doubleClass, doubleConstructor, param.value.d);
        return doubleObject;
    }

    void* CreateCharObject(Helper helper, const Param& param) {
        auto env = helper->env;
        jclass characterClass = env->FindClass("java/lang/Character");
        jmethodID valueOfMethod = env->GetStaticMethodID(characterClass, "valueOf", "(C)Ljava/lang/Character");
        jobject characterObject = env->CallStaticObjectMethod(characterClass, valueOfMethod, param.value.c);

        return characterObject;
    }

    void* CreateByteObject(Helper helper, const Param& param) {
        auto env = helper->env;
        jclass byteClass = env->FindClass("java/lang/Byte");
        jmethodID byteConstructor = env->GetMethodID(byteClass, "<init>", "(B)V");
        jobject byteObject = env->NewObject(byteClass, byteConstructor, param.value.b);
        return byteObject;
    }

    void* CreateStringObject(Helper helper, const Param& param) {
        auto env = helper->env;
        jstring stringObject = env->NewStringUTF(param.value.s);
        return stringObject;
    }

    void DeleteObjectRef(Helper helper, void* p)
    {
        jobject obj = (jobject) p;
        if(obj == nullptr) {
            helper->msg("DeleteObjectRef - Nullptr Object", WarnMsg);
            return;
        }

        auto* env = helper->env;
        env->DeleteLocalRef(obj);
        delete obj;
    }

} // namespace jni