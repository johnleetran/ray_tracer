#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include "matrix3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"
#include "vec3d.hpp"

#pragma once
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

                Ray3D<T> transform(Ray_Tracer::Matrix3D::Matrix3D<T> mat){
                    Ray_Tracer::Tuple3D::Tuple3D<T> new_origin = mat * origin;
                    Ray_Tracer::Vec3D::Vec3D<T> new_direction = mat * direction;
                    Ray3D ray{new_origin, new_direction};
                    return ray;
                }
        };
    }
}