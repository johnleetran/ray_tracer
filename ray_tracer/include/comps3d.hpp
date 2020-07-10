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
    class Comps3D
    {
    public:
        T t;
        Sphere3D<T> object;
        Tuple3D<T> point;
        Vec3D<T> eyev;
        Vec3D<T> normalv;
        bool inside;
        Tuple3D<T> over_point;
        Comps3D(){}

        Comps3D(T t, Sphere3D<T> object, Tuple3D<T> point, Vec3D<T> eyev, Vec3D<T> normalv, bool inside) : t(t), object(object), point(point), eyev(eyev), normalv(normalv), inside(inside)
        {
            
        }
    };
} // namespace Ray_Tracer