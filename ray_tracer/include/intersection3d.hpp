#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <optional>
#include <vector>
#include "sphere3d.hpp"
#include "ray3d.hpp"
#include "tuple3d.hpp"
#include "vec3d.hpp"

#pragma once
namespace Ray_Tracer
{
        template <typename T>
        class Intersection3D
        {
        public:
            T t;
            Ray_Tracer::Sphere3D::Sphere3D<T> object;
            Intersection3D(){}
            Intersection3D(T t, Ray_Tracer::Sphere3D::Sphere3D<T> sphere) : t(t), object(sphere) {}

            static std::optional< std::vector<T> > intersect(Ray_Tracer::Ray3D::Ray3D<T> ray, Ray_Tracer::Sphere3D::Sphere3D<T> sphere)
            {
                ray = ray.transform(sphere.transform_matrix.get_inverse());

                Ray_Tracer::Tuple3D::Tuple3D<T> sphere_to_ray = ray.origin - sphere.origin;
                T a = ray.direction.dot(ray.direction);
                T b = 2 * ray.direction.dot(Ray_Tracer::Vec3D::Vec3D<T>{sphere_to_ray.x, sphere_to_ray.y, sphere_to_ray.z});
                T c = (sphere_to_ray.dot(sphere_to_ray)) - 1;
                float discriminant = (b * b) - (4 * a * c);
                if (discriminant < 0)
                {
                    return std::nullopt;
                }

                T t1 = (-b - std::sqrt(discriminant)) / (a * 2);
                T t2 = (-b + std::sqrt(discriminant)) / (a * 2);

                std::vector<T> t = {t1, t2};
                std::sort(t.begin(), t.end());
                return {t};
            }
        };
} // namespace Ray_Tracer