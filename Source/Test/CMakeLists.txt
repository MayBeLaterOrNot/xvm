cmake_minimum_required(VERSION 3.15)

set(PROJECTNAME Test)

file(GLOB_RECURSE tests
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

enable_testing()

add_executable(
    ${PROJECTNAME}
    main.cpp
    ${xvm}
    ${tests})
target_link_libraries(
    ${PROJECTNAME}
    gtest_main)
    
if (MSVC)
	target_compile_options(${PROJECTNAME} PRIVATE "/W3") # warning level 3
	target_compile_options(${PROJECTNAME} PRIVATE "/MP") # Multi-processor compilation
endif()

set_property(TARGET ${PROJECTNAME} PROPERTY CXX_STANDARD 20)

include_directories("${CMAKE_SOURCE_DIR}/Source")

include(GoogleTest)
gtest_discover_tests(${PROJECTNAME})
