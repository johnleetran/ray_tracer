#include "./color3d.hpp"
#include "./vec3d.hpp"
#include "./tuple3d.hpp"

#pragma once
namespace Ray_Tracer{
    template<typename T>
    class PointLight3D{
        public:
        Ray_Tracer::Color3D<T> intensity;
        Ray_Tracer::Tuple3D<T> position;
        PointLight3D(){};
        PointLight3D(Ray_Tracer::Tuple3D<T> position, Ray_Tracer::Color3D<T> intensity) : position(position), intensity(intensity) {}
    };
}