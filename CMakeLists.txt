cmake_minimum_required(VERSION 3.12)

project(app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND 
    SOURCES_FILES
        ray_tracer/include/canvas3d.hpp
        ray_tracer/include/color3d.hpp
        ray_tracer/include/intersection3d.hpp
        ray_tracer/include/intersection3d_collection.hpp
        ray_tracer/include/material3d.hpp
        ray_tracer/include/matrix3d.hpp
        ray_tracer/include/point_light3d.hpp
        ray_tracer/include/ray3d.hpp
        ray_tracer/include/tuple3d.hpp
        ray_tracer/include/vec3d.hpp
)

add_subdirectory(external/googletest)
add_subdirectory(ray_tracer)


add_executable(app main.cpp)
add_compile_options(-Wno-unused-variable)
target_sources(
    app 
    PRIVATE 
        main.cpp 
        ${SOURCES_FILES}
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
        ${SOURCES_FILES}
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