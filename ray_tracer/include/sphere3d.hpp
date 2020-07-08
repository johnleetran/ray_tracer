#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "material3d.hpp"
#include "matrix3d.hpp"
#include "tuple3d.hpp"
#include "vec3d.hpp"

#pragma once
namespace Ray_Tracer
{
    template <typename T>
    class Sphere3D
    {
    public:
        float radius;
        std::string id;
        Ray_Tracer::Tuple3D<T> origin{0,0,0};
        Ray_Tracer::Matrix3D<T> transform_matrix{};
        Ray_Tracer::Material3D<T> material{};
        Sphere3D() {}

        Sphere3D(float radius, std::string id) : radius(radius), id(id)
        {
            transform_matrix = Ray_Tracer::Matrix3D<T>::get_generic_identity_matrix();
        }

        Ray_Tracer::Matrix3D<T> get_transform(){
            return transform_matrix;
        }

        void transform(Ray_Tracer::Matrix3D<T> mat)
        {
            transform_matrix = mat * transform_matrix;
        }

        Ray_Tracer::Vec3D<T> normalize_at(Ray_Tracer::Tuple3D<T> point)
        {
            Ray_Tracer::Tuple3D<T> object_point = transform_matrix.get_inverse() * point;
            Ray_Tracer::Tuple3D<T> object_normal = object_point - origin;
            Ray_Tracer::Tuple3D<T> world_normal = transform_matrix.get_inverse().transpose() * object_normal;
            world_normal.w = 0;
            world_normal = world_normal.normalize();
            return Ray_Tracer::Vec3D<T>{world_normal.x, world_normal.y, world_normal.z};
        }
    };
} // namespace Ray_Tracer