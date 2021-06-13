cmake_minimum_required(VERSION 3.15)

set(PROJECTNAME xvmTest)

file(GLOB_RECURSE tests
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

file(GLOB_RECURSE xvm
    ${CMAKE_SOURCE_DIR}/src/xvm/*.h
    ${CMAKE_SOURCE_DIR}/src/xvm/*.inl
    ${CMAKE_SOURCE_DIR}/src/xvm/*.natvis)

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${src})

enable_testing()

if (MSVC)
    add_compile_options(/W3) # warning level 3
	add_compile_options(/MP) # Multi-processor compilation
endif()

add_executable(
    ${PROJECTNAME}
    main.cpp
    ${xvm}
    ${tests})
target_link_libraries(
    ${PROJECTNAME}
    gtest_main)

set_property(TARGET ${PROJECTNAME} PROPERTY CXX_STANDARD 20)

include_directories("${CMAKE_SOURCE_DIR}/src")

include(GoogleTest)
gtest_discover_tests(${PROJECTNAME})
