#include <cmath>
#include <iostream>
#include <vector>
#include "./tuple3d.hpp"
#include "./vec3d.hpp"

namespace Ray_Tracer{
    namespace Ray3D {
        template <typename T>
        class Ray3D{
            public:
                Ray_Tracer::Tuple3D::Tuple3D<T> origin;
                Ray_Tracer::Vec3D::Vec3D<T> direction;
                Ray3D(Ray_Tracer::Tuple3D::Tuple3D<T> origin, Ray_Tracer::Vec3D::Vec3D<T> direction) : origin(origin), direction(direction){ }

                Ray_Tracer::Tuple3D::Tuple3D<T> position(float t)
                {
                    return origin + direction * t;
                }
        };
    }
}