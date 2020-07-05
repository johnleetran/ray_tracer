#include <tuple>
#include <cmath>

#pragma once

namespace Ray_Tracer {
namespace Vec3D{

    //my 3d vectors
    template <typename T>
    struct Vec3D
    {
        T x;
        T y;
        T z;
    };

    /********************/
    /* start of vectors */
    /********************/
    template <typename T>
    Vec3D<T> add(Vec3D<T> t1, Vec3D<T> t2)
    {
        T x = t1.x + t2.x;
        T y = t1.y + t2.y;
        T z = t1.z + t2.z;

        Vec3D<T> sum = {x, y, z};
        return sum;
    }

    template <typename T>
    Vec3D<T> subtract(Vec3D<T> t1, Vec3D<T> t2)
    {
        T x = t1.x - t2.x;
        T y = t1.y - t2.y;
        T z = t1.z - t2.z;

        Vec3D<T> diff = {x, y, z};
        return diff;
    }

    template <typename T>
    Vec3D<T> negate(Vec3D<T> t1)
    {
        Vec3D<T> zero = {0, 0, 0};
        Vec3D<T> neg = subtract(zero, t1);
        return neg;
    }

    template <typename T, typename U>
    Vec3D<T> multiply(Vec3D<T> t1, U multiplier)
    {
        T x = t1.x * multiplier;
        T y = t1.y * multiplier;
        T z = t1.z * multiplier;
        T w = t1.w * multiplier;

        Vec3D<T> product = {x, y, z, w};
        return product;
    }

    template <typename T>
    T magnitude(Vec3D<T> t1)
    {
        T x = t1.x * t1.x;
        T y = t1.y * t1.y;
        T z = t1.z * t1.z;

        T product = std::sqrt(x + y + z);
        return product;
    }

    template <typename T>
    Vec3D<T> normalize(Vec3D<T> t1)
    {
        T x = t1.x / magnitude(t1);
        T y = t1.y / magnitude(t1);
        T z = t1.z / magnitude(t1);

        Vec3D<T> normalized = {x, y, z};
        return normalized;
    }

    template <typename T>
    T dot(Vec3D<T> t1, Vec3D<T> t2)
    {
        T x = t1.x * t2.x;
        T y = t1.y * t2.y;
        T z = t1.z * t2.z;

        T d = x + y + z;
        return d;
    }

    template <typename T>
    Vec3D<T> cross(Vec3D<T> t1, Vec3D<T> t2)
    {
        T x = t1.y * t2.z - t1.z * t2.y;
        T y = t1.z * t2.x - t1.x * t2.z;
        T z = t1.x * t2.y - t1.y * t2.x;

        Vec3D<T> c = {x, y, z};
        return c;
    }
}
} // namespace Ray_Tracer
