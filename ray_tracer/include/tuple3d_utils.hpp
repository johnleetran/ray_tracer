#include <tuple>
#include <cmath>

#pragma once

namespace Ray_Tracer{
namespace Tuple3D{
    //my 3d tuples
    template <typename T>
    struct Tuple3D
    {
        T x;
        T y;
        T z;
        T w;
    };

    template <typename T>
    Tuple3D<T> add(Tuple3D<T> t1, Tuple3D<T> t2)
    {
        T x = t1.x + t2.x;
        T y = t1.y + t2.y;
        T z = t1.z + t2.z;
        T w = t1.w + t2.w;

        Tuple3D<T> sum = {x, y, z, w};
        return sum;
    }

    template <typename T>
    Tuple3D<T> subtract(Tuple3D<T> t1, Tuple3D<T> t2)
    {
        T x = t1.x - t2.x;
        T y = t1.y - t2.y;
        T z = t1.z - t2.z;
        T w = t1.w - t2.w;

        Tuple3D<T> diff = {x, y, z, w};
        return diff;
    }

    template <typename T>
    Tuple3D<T> negate(Tuple3D<T> t1)
    {
        Tuple3D<T> zero = {0, 0, 0, 0};
        Tuple3D<T> neg = subtract(zero, t1);
        return neg;
    }

    template <typename T, typename U>
    Tuple3D<T> multiply(Tuple3D<T> t1, U multiplier)
    {
        T x = t1.x * multiplier;
        T y = t1.y * multiplier;
        T z = t1.z * multiplier;
        T w = t1.w * multiplier;

        Tuple3D<T> product = {x, y, z, w};
        return product;
    }

    template <typename T>
    T magnitude(Tuple3D<T> t1)
    {
        T x = t1.x * t1.x;
        T y = t1.y * t1.y;
        T z = t1.z * t1.z;
        T w = t1.w * t1.w;

        T mag = std::sqrt(x + y + z + w);
        return mag;
    }

    template <typename T>
    Tuple3D<T> normalize(Tuple3D<T> t1)
    {
        T x = t1.x / magnitude(t1);
        T y = t1.y / magnitude(t1);
        T z = t1.z / magnitude(t1);
        T w = t1.w / magnitude(t1);

        Tuple3D<T> normalized = {x, y, z, w};
        return normalized;
    }
    template <typename T>
    T dot(Tuple3D<T> t1, Tuple3D<T> t2)
    {
        T x = t1.x * t2.x;
        T y = t1.y * t2.y;
        T z = t1.z * t2.z;
        T w = t1.w * t2.w;

        T dot = x + y + z + w;
        return dot;
    }
}
} // namespace Ray_Tracer
