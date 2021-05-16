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

include_directories("${CMAKE_SOURCE_DIR}/src")
add_executable(
    ${PROJECTNAME}
    main.cpp
    ${xvm}
    ${tests}
)
target_link_libraries(
    ${PROJECTNAME}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECTNAME})
