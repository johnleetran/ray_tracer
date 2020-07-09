#include "color3d.hpp"
#include "intersection3d.hpp"
#include "intersection3d_collection.hpp"

#include "camera3d.hpp"
#include "matrix3d.hpp"
#include "ray3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"
#include "vec3d.hpp"

#pragma once
using namespace Ray_Tracer;

namespace Ray_Tracer
{
    template <typename T>
    class RayForPixel3D
    {
    public:
        RayForPixel3D(){}
        
        static Ray3D<T> ray_for_pixel(Camera3D<T> camera, T x, T y){
            T xoffset = (x + 0.5) * camera.pixel_size;
            T yoffset = (y + 0.5) * camera.pixel_size;

            T world_x = camera.half_width - xoffset;
            T world_y = camera.half_height - yoffset;

            Tuple3D<T> world_point{world_x, world_y, -1};

            Tuple3D<T> pixel = camera.transform_matrix.get_inverse() * world_point;
            Tuple3D<T> origin = camera.transform_matrix.get_inverse() * Tuple3D<T>{0, 0, 0};
            Tuple3D<T> direction_tuple = (pixel - origin);
            Vec3D<T> direction = Vec3D<T>{direction_tuple.x , direction_tuple.y, direction_tuple.z}.normalize();
            Ray3D<T> ray { origin, direction };
            return ray;
        }
    };
} // namespace Ray_Tracer