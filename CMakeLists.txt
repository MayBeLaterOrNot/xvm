cmake_minimum_required(VERSION 3.16)

# Group CMakePredefinedTargets into a folder filter
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_SYSTEM_VERSION 10.0.19041.0)
project(xvm)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Bin")
set(CMAKE_CXX_STANDARD_REQUIRED)
add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/662fe38e44900c007eccb65a5d2ea19df7bd520e.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(Source)
