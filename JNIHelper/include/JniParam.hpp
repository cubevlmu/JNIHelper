#pragma once

namespace jni {

    enum JavaType {
        
        JavaInt,
        JavaDouble,
        JavaFloat,
        JavaBool,
        JavaChar,
        JavaByte,
        JavaLong,

        JavaIntObject,
        JavaStringObject,
        JavaLongObject,
        JavaDoubleObject,
        JavaFloatObject,
        JavaCharObject,
        JavaByteObject,
        
        JavaByteArray,
        JavaObjects,
        JavaVoid
    };

    union JniObject {
        const char* s;
        int i;
        float f;
        double d;
        bool b;
        char c;
        signed char byte;
        signed char* byteArray;
        long l;
        void* j;
    };

    struct Param {
        JniObject value;
        JavaType type;
    };

}