cmake_minimum_required(VERSION 3.12)

project(app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/googletest)
add_subdirectory(ray_tracer)

add_executable(app main.cpp)
target_sources(
    app 
    PRIVATE 
        main.cpp 
        ray_tracer/include/tuple3d_utils.hpp
        ray_tracer/include/vec3d_utils.hpp
)

target_include_directories(app 
    PUBLIC 
        ray_tracer/include
)
target_link_libraries(
    app 
    PRIVATE 
        ray_tracer
)

# cmake portion for running unit tests 
option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

add_executable(cpp_test "")

target_sources(cpp_test 
    PRIVATE 
        test.cpp 
        tests/tuple3d_utils_test.hpp
        tests/vec3d_utils_test.hpp
        )

target_include_directories(cpp_test 
    PUBLIC 
        external/googletest/googletest/include 
        tests
        ray_tracer/include
)
target_link_libraries(
    cpp_test 
        PRIVATE 
            gtest
            ray_tracer
)

enable_testing()

add_test(
    NAME cpp_test
    COMMAND $<TARGET_FILE:cpp_test>
)