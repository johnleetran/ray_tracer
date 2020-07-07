#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "matrix3d.hpp"
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
            Ray_Tracer::Matrix3D::Matrix3D<T> transform_matrix{};
            Sphere3D() {}

            Sphere3D(float radius, std::string id) : radius(radius), id(id)
            {
                transform_matrix = Ray_Tracer::Matrix3D::Matrix3D<T>::get_generic_identity_matrix();
            }

            Ray_Tracer::Matrix3D::Matrix3D<T> get_transform(){
                return transform_matrix;
            }

            void transform(Ray_Tracer::Matrix3D::Matrix3D<T> mat)
            {
                transform_matrix = mat * transform_matrix;
            }
        };
    } // namespace Sphere3D
} // namespace Ray_Tracer