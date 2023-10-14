#include <jni.h>

#include "JniCallbackHelper.hpp"
#include "JniHelper.hpp"
#include "JniFields.hpp"
#include "JniParam.hpp"
#include "Test.h"

void test() {
    printf("On Test Call()\n");
    jni::Helper ins = jni::createHelper();

    jni::Param arg1;
    arg1.value.i = 12;
    arg1.type = jni::JavaInt;

    jni::JavaObject clz = jni::FindStaticClass(ins, "Test");
    jni::JavaMethod mtd = jni::CreateInvoke(ins, clz, jni::JavaType::JavaInt, "test", "(I)I", { arg1 });
    jni::Invoke(ins, mtd);
    jni::Param* p = jni::GetReturnValue(mtd);
    printf("Result From Java Method %i\n", p->value.i);
}

void test1(void* instance) {
    jni::Helper ins = jni::createHelper();
    
    jni::Param p {};
    p.type = jni::JavaType::JavaObjects;
    p.value.j = instance;


    jni::JavaObject obj = jni::CreateByJObj(ins, p);
    jni::JavaField fd = jni::CreateFieldInvoke(ins, obj, jni::JavaType::JavaInt, "testValue", "I");

    jni::Param p1 {};
    p1.type = jni::JavaType::JavaInt;
    p1.value.i = 19198;
    jni::SetFieldValue(ins, fd, p1);

    auto* result = jni::GetFieldValue(ins, fd);

    printf("Field 'testValue' : %i", result->value.i);
}