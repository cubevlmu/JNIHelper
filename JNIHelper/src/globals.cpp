#include <jni.h>

#include "JniCallbackHelper.hpp"
#include "JniHelper.hpp"
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