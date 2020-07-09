#include "color3d.hpp"
#include "intersection3d.hpp"
#include "intersection3d_collection.hpp"

#include "matrix3d.hpp"
#include "point_light3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"
#include "vec3d.hpp"

#pragma once
using namespace Ray_Tracer;

namespace Ray_Tracer
{
    template <typename T>
    class Camera3D
    {
    public:
        T hsize;
        T vsize;
        T field_of_view;

        //calculated
        Matrix3D<T> transform_matrix;
        T half_width;
        T half_height;
        T pixel_size;

        Camera3D(){}
        Camera3D(T hsize, T vsize, T field_of_view):hsize(hsize), vsize(vsize), field_of_view(field_of_view) {
            transform_matrix = Matrix3D<T>::get_generic_identity_matrix();
            pixel_size = calculate_pixel_size();
        }

        T calculate_pixel_size(){
            T half_view = std::tanf( field_of_view / 2.f );
            T aspect = hsize / vsize;

            if(aspect >= 1.f){
                half_width = half_view;
                half_height = half_view / aspect;
            }else{
                half_width = half_view * aspect;
                half_height = half_view;
            }
            return half_width * 2.f / hsize;
        }

        static Matrix3D<T> view_transform(Tuple3D<T> from, Tuple3D<T> to, Vec3D<T> up)
        {
            Tuple3D<T> tmp = to - from;
            Tuple3D<T> foward_tuple = tmp.normalize();
            Vec3D<T> forward{foward_tuple.x, foward_tuple.y, foward_tuple.z};
            Vec3D<T> upn = up.normalize();
            Vec3D<T> left = forward.cross(up);
            Vec3D<T> true_up = left.cross(forward);
            std::vector<std::vector<T>> mat{
                {left.x, left.y, left.z, 0},
                {true_up.x, true_up.y, true_up.z, 0},
                {-forward.x, -forward.y, -forward.z, 0},
                {0, 0, 0, 1}};
            Matrix3D<T> orientation{mat};
            Matrix3D<T> tranlation_matrix = orientation.translate(-from.x, -from.y, -from.z);
            return orientation * tranlation_matrix;
        }

        Matrix3D<T> transform()
        {
            return transform_matrix;
        }
    };
} // namespace Ray_Tracer