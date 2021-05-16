cmake_minimum_required(VERSION 3.15)

# Group CMakePredefinedTargets into a folder filter
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_SYSTEM_VERSION 10.0.19041.0)
project(xvm)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/662fe38e44900c007eccb65a5d2ea19df7bd520e.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(benchmark)
add_subdirectory(test)