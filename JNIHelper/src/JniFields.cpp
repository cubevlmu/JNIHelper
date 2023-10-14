#include "JniFields.hpp"

#include "_JniCallbackHelper.hpp"
#include "_JniFields.hpp"
#include "_JniHelper.hpp"
#include <jni.h>

namespace jni {

    lib_api JavaField CreateFieldInvoke(Helper helper, JavaObject object, JavaType exceptType, const char* name, const char* sig)
    {
        auto* env = helper->env;
        auto* clazz = object->_class;

        jfieldID id = object->isStatic ?
                     env->GetStaticFieldID(clazz, name, sig) :
                     env->GetFieldID(clazz, name, sig);
        if(id == nullptr) {
            helper->error("Can't Found Field", false);
            return nullptr;
        }
        
        auto* jf = new JavaFieldInvoke();
        jf->clazz = clazz;
        jf->instance = object->_instance;
        jf->fid = id;
        jf->name = name;
        jf->sig = sig;
        jf->isStatic = object->isStatic;
        jf->exceptType = exceptType;

#ifdef HelperDebug
        std::cout << "JavaFieldInvoke \n" 
                  << "Clazz : " << jf->clazz << "\n"
                  << "Instance : " << jf->instance << "\n"
                  << "FID : " << jf->fid << "\n"
                  << "Name : " << jf->name << "\n"
                  << "Sig : " << jf->sig << "\n"
                  << "isStatic : " << jf->isStatic << "\n"
                  << "exceptType : " << jf->exceptType << "\n";
#endif

        return jf;
    }

    static void SetField(JavaField fid, JNIEnv *env, const Param& p) {
        
        switch (fid->exceptType)
        {    
        case JavaInt:{
            if(fid->isStatic) env->SetStaticIntField(fid->clazz, fid->fid, p.value.i);
            else             env->SetIntField(fid->instance, fid->fid, p.value.i);
        }
        break;
        case JavaDouble:{
            if(fid->isStatic) env->SetStaticDoubleField(fid->clazz, fid->fid, p.value.d);
            else             env->SetDoubleField(fid->instance, fid->fid, p.value.d);
        }
        break;
        case JavaFloat:{
            if(fid->isStatic) env->SetStaticFloatField(fid->clazz, fid->fid, p.value.f);
            else             env->SetFloatField(fid->instance, fid->fid, p.value.f);
        }
        break;
        case JavaBool:{
            if(fid->isStatic) env->SetStaticBooleanField(fid->clazz, fid->fid, p.value.b);
            else             env->SetBooleanField(fid->instance, fid->fid, p.value.b);
        }
        break;
        case JavaChar:{
            if(fid->isStatic) env->SetStaticCharField(fid->clazz, fid->fid, p.value.c);
            else             env->SetCharField(fid->instance, fid->fid, p.value.c);
        }
        break;
        case JavaByte:{
            if(fid->isStatic) env->SetStaticByteField(fid->clazz, fid->fid, p.value.byte);
            else             env->SetByteField(fid->instance, fid->fid, p.value.b);
        }
        break;
        case JavaLong:{
            if(fid->isStatic) env->SetStaticLongField(fid->clazz, fid->fid, p.value.l);
            else             env->SetLongField(fid->instance, fid->fid, p.value.l);
        }
        break;
        case JavaIntObject:
        case JavaStringObject:
        case JavaLongObject:
        case JavaDoubleObject:
        case JavaFloatObject:
        case JavaCharObject:
        case JavaByteObject:
        case JavaByteArray:
        case JavaObjects:{
            if(fid->isStatic) env->SetStaticObjectField(fid->clazz, fid->fid, (jobject)p.value.j);
            else             env->SetObjectField(fid->instance, fid->fid, (jobject)p.value.j);
        }
        break;
        case JavaVoid:
        break;
        }
    }

    static void GetField(JavaField fid, JNIEnv *env, Param* p) {
        p->type = fid->exceptType;

        switch (fid->exceptType)
        {    
        case JavaInt:{
            auto result = fid->isStatic ? 
                          env->GetStaticIntField(fid->clazz, fid->fid) : 
                          env->GetIntField(fid->instance, fid->fid);
            p->value.i = result;
        }
        break;
        case JavaDouble:{
            auto result = fid->isStatic ? 
                          env->GetStaticDoubleField(fid->clazz, fid->fid) : 
                          env->GetDoubleField(fid->instance, fid->fid);
            p->value.d = result;
        }
        break;
        case JavaFloat:{
            auto result = fid->isStatic ? 
                          env->GetStaticFloatField(fid->clazz, fid->fid) : 
                          env->GetFloatField(fid->instance, fid->fid);
            p->value.f = result;
        }
        break;
        case JavaBool:{
            auto result = fid->isStatic ? 
                          env->GetStaticBooleanField(fid->clazz, fid->fid) : 
                          env->GetBooleanField(fid->instance, fid->fid);
            p->value.b = result;
        }
        break;
        case JavaChar:{
            auto result = fid->isStatic ? 
                          env->GetStaticCharField(fid->clazz, fid->fid) : 
                          env->GetCharField(fid->instance, fid->fid);
            p->value.c = result;
        }
        break;
        case JavaByte:{
            auto result = fid->isStatic ? 
                          env->GetStaticByteField(fid->clazz, fid->fid) : 
                          env->GetByteField(fid->instance, fid->fid);
            p->value.byte = result;
        }
        break;
        case JavaLong:{
            auto result = fid->isStatic ? 
                          env->GetStaticLongField(fid->clazz, fid->fid) : 
                          env->GetLongField(fid->instance, fid->fid);
            p->value.l = result;
        }
        break;
        case JavaIntObject:
        case JavaStringObject:
        case JavaLongObject:
        case JavaDoubleObject:
        case JavaFloatObject:
        case JavaCharObject:
        case JavaByteObject:
        case JavaByteArray:
        case JavaObjects:{
            auto* result = fid->isStatic ? 
                          env->GetStaticObjectField(fid->clazz, fid->fid) : 
                          env->GetObjectField(fid->instance, fid->fid);
            p->value.j = result;
        }
        break;
        case JavaVoid:
        break;
        }
    }

    Param* GetFieldValue(Helper helper, JavaField object)
    {
        auto* env = helper->env;
        Param* p = new Param();
        GetField(object, env, p);
        return p;
    }

    bool SetFieldValue(Helper helper, JavaField object, const Param& value)
    {
        auto* env = helper->env;
        SetField(object, env, value);
        return true;
    }
    
    void DestroyFieldInvoke(Helper helper, JavaField f)
    {
        
    }
}