cmake_minimum_required(VERSION 3.15)

# FetchContent_Declare(googlebenchmark
#     GIT_REPOSITORY https://github.com/google/benchmark.git
#     GIT_TAG main) # need master for benchmark::benchmark
# 
# FetchContent_MakeAvailable(
#     googlebenchmark)

set(PROJECTNAME Benchmark)

file(GLOB_RECURSE benchmarks
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(
    ${PROJECTNAME}
    main.cpp
    ${xvm}
    ${benchmarks})
    
if (MSVC)
	target_compile_options(${PROJECTNAME} PRIVATE "/W3") # warning level 3
	target_compile_options(${PROJECTNAME} PRIVATE "/MP") # Multi-processor compilation
endif()

set_property(TARGET ${PROJECTNAME} PROPERTY CXX_STANDARD 20)

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Dependencies/google-benchmark/include")

# target_link_libraries(${PROJECTNAME} benchmark::benchmark)
target_link_libraries(${PROJECTNAME} debug ${CMAKE_SOURCE_DIR}/Dependencies/google-benchmark/lib/Debug/benchmark.lib)
target_link_libraries(${PROJECTNAME} optimized ${CMAKE_SOURCE_DIR}/Dependencies/google-benchmark/lib/Release/benchmark.lib)
