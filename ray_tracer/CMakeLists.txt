project(ray_tracer)

#target_include_directories(ray_tracer PRIVATE includes)
add_library(ray_tracer 
    STATIC
        src/tuple3d_utils.cpp
)