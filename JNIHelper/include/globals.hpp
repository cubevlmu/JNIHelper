#pragma once

#ifndef _WIN32
#include <signal.h> // SIGTRAP
#endif

#include <iostream>
#include <string>
#include <list>

 
// #define unix_base defined(__APPLE__) || defined(__ANDROID__) || defined (__linux__)
#define winnt define(_WIN32)

#if (defined(__APPLE__) || defined(__ANDROID__) || defined(__linux__)) && defined(compile_lib)
#define lib_api __attribute__((visibility ("default")))
#elif defined(_WIN32) && defined(compile_lib)
#define lib_api __declspec(dllexport)
#else
#define lib_api
#endif


#ifdef _WIN32
#define cb_debug_break() __debugbreak()
#define cb_inline __forceinline
#define cb_restrict __restrict
#else
#define cb_debug_break() raise(SIGTRAP)
#define cb_inline __attribute__((always_inline)) inline
#define cb_restrict __restrict__
#endif

#define ASSERT(x)                                  \
    do                                             \
    {                                              \
        const volatile bool _assert_result = !(x); \
        if (_assert_result)   {                     \
            cb_debug_break();                      \
                             }                     \
    } while (false)




#define CHECK_EMPTY(POINTER, MSG)                         \
   if (POINTER != nullptr)                                \
   {                                                      \
      CError("A Pointer Is Not NULL, Message: {0}", MSG); \
      throw std::system_error(std::error_code(), MSG);         \
   }

void test();
void test1(void* instance);