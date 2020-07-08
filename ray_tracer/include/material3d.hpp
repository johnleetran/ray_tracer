#include "./color3d.hpp"
#include "./vec3d.hpp"
#include "./tuple3d.hpp"

#pragma once
namespace Ray_Tracer
{
    template <typename T>
    class Material3D
    {
    public:
        Ray_Tracer::Color3D::Color3D<T> color {1,1,1};
        float ambient = 0.1;
        float diffuse = 0.9;
        float specular = 0.9;
        float shininess = 200.0;
        Material3D() {}
    };
} // namespace Ray_Tracer