cmake_minimum_required(VERSION 3.15)

project(JNIHelpers)

IF (APPLE)
message(STATUS "[Info] Compile System Is Apple")
set(COMPILE_HEADER cb_unix_base)
set(PLATFORM_HEADER cb_macOS)
ELSEIF (WIN32)
message(STATUS "[Info] Compile System Is Window")
set(COMPILE_HEADER cb_winnt)
set(PLATFORM_HEADER cb_windows)
ELSEIF (LINUX)
message(STATUS "[Info] Compile System Is LINUX")
set(COMPILE_HEADER cb_unix_base)
set(PLATFORM_HEADER cb_linux)
ELSE()

ENDIF()

add_subdirectory("JNIHelper")

set(HelperIncludeDir ${CMAKE_CURRENT_SOURCE_DIR}/JNIHelper/include CACHE INTERNAL "Include Dir")