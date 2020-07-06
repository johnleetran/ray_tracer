project(ray_tracer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#target_include_directories(ray_tracer PRIVATE includes)
add_library(ray_tracer 
    STATIC
        src/tuple3d.cpp
        src/vec3d.cpp
)
