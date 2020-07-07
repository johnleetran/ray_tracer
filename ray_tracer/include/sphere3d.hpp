#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "tuple3d.hpp"
#include "vec3d.hpp"

#pragma once
namespace Ray_Tracer
{
    namespace Sphere3D
    {
        template <typename T>
        class Sphere3D
        {
        public:
            float radius;
            std::string id;
            Ray_Tracer::Tuple3D::Tuple3D<T> origin{0,0,0};
            Sphere3D(float radius, std::string id) : radius(radius), id(id) {
                
            }
        };
    } // namespace Sphere3D
} // namespace Ray_Tracer