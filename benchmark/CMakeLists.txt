cmake_minimum_required(VERSION 3.15)

# FetchContent_Declare(googlebenchmark
#     GIT_REPOSITORY https://github.com/google/benchmark.git
#     GIT_TAG main) # need master for benchmark::benchmark
# 
# FetchContent_MakeAvailable(
#     googlebenchmark)

set(PROJECTNAME xvmBenchmark)

file(GLOB_RECURSE benchmarks
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

file(GLOB_RECURSE xvm
    ${CMAKE_SOURCE_DIR}/src/xvm/*.h
    ${CMAKE_SOURCE_DIR}/src/xvm/*.inl
    ${CMAKE_SOURCE_DIR}/src/xvm/*.natvis)

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${src})

if (MSVC)
    add_compile_options(/W3) # warning level 3
	add_compile_options(/MP) # Multi-processor compilation
endif()

add_executable(
    ${PROJECTNAME}
    main.cpp
    ${xvm}
    ${benchmarks})

set_property(TARGET ${PROJECTNAME} PROPERTY CXX_STANDARD 20)

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_SOURCE_DIR}/ext/google-benchmark/include")

# target_link_libraries(${PROJECTNAME} benchmark::benchmark)
target_link_libraries(${PROJECTNAME} debug ${CMAKE_SOURCE_DIR}/ext/google-benchmark/lib/Debug/benchmark.lib)
target_link_libraries(${PROJECTNAME} optimized ${CMAKE_SOURCE_DIR}/ext/google-benchmark/lib/Release/benchmark.lib)
