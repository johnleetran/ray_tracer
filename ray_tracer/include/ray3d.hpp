#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
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

                std::vector<T> intersect(Ray_Tracer::Sphere3D::Sphere3D<T> sphere)
                {
                    Ray_Tracer::Tuple3D::Tuple3D<T> sphere_to_ray = origin - sphere.origin;
                    T a = direction.dot(direction);
                    T b = 2 * direction.dot(Ray_Tracer::Vec3D::Vec3D<T>{sphere_to_ray.x, sphere_to_ray.y, sphere_to_ray.z});
                    T c = (sphere_to_ray.dot(sphere_to_ray)) - 1;
                    float discriminant = (b * b) - (4 * a * c);
                    if (discriminant < 0){
                        std::vector<T> empty_vector;
                        return empty_vector;
                    }

                    T t1 = (-b - std::sqrt(discriminant)) / (a * 2);
                    T t2 = (-b + std::sqrt(discriminant)) / (a * 2);

                    std::vector<T> t = {t1, t2};
                    std::sort(t.begin(), t.end());
                    return t;
                }
        };
    }
}