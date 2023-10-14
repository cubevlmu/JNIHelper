cmake_minimum_required(VERSION 3.15)

project(JNIHelper LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(JNIHelper SHARED 
    "src/globals.cpp"
    "src/JniCallbackHelper.cpp"
    "src/JniHelper.cpp"
    "src/_JNICaller.cpp"
    "src/JniFields.cpp"
)

## =======================
## Init JNI System Path
## =======================
IF(APPLE)
set(jni_path ${CMAKE_SOURCE_DIR}/jni/darwin)
ELSEIF(WIN32)
set(jni_path ${CMAKE_SOURCE_DIR}/jni/win32)
ELSEIF(LINUX)
set(jni_path ${CMAKE_SOURCE_DIR}/jni/linux)
ENDIF()
## =======================

target_include_directories(JNIHelper PRIVATE 
    ${CMAKE_SOURCE_DIR}/jni
    ${jni_path}

    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source
)

target_compile_definitions(JNIHelper PRIVATE 
    compile_lib
    #HelperDebug
)