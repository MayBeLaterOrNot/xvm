cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE xvm
    ${CMAKE_SOURCE_DIR}/Source/xvm/*.h
    ${CMAKE_SOURCE_DIR}/Source/xvm/*.inl
    ${CMAKE_SOURCE_DIR}/Source/xvm/*.natvis)

add_subdirectory(Benchmark)
add_subdirectory(Test)