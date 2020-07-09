#include <cmath>
#include <iostream>

#pragma once
namespace Ray_Tracer
{
    template <typename T>
    class Vec3D
    {
    public:
        T x;
        T y;
        T z;
        int size = 4;

        Vec3D() : x(0), y(0), z(0) {}
        Vec3D(T x, T y, T z) : x(x), y(y), z(z){}
        T magnitude()
        {
            T res_x = x * x;
            T res_y = y * y;
            T res_z = z * z;

            T mag = std::sqrt(res_x + res_y + res_z);
            return mag;
        }

        Vec3D<T> normalize()
        {
            Vec3D t1{x,y,z};
            T res_x = x / magnitude();
            T res_y = y / magnitude();
            T res_z = z / magnitude();

            Vec3D<T> normalized = {res_x, res_y, res_z};
            return normalized;
        }

        T dot(Vec3D<T> t1)
        {
            T res_x = t1.x * x;
            T res_y = t1.y * y;
            T res_z = t1.z * z;

            T dot = res_x + res_y + res_z;
            return dot;
        }

        Vec3D<T> cross(Vec3D<T> t2)
        {
            Vec3D<T> t1 = *this;
            T x = t1.y * t2.z - t1.z * t2.y;
            T y = t1.z * t2.x - t1.x * t2.z;
            T z = t1.x * t2.y - t1.y * t2.x;

            Vec3D<T> crs = {x, y, z};
            return crs;
        }

        T getValueByIndex(int index) const
        {
            if (index == 0)
            {
                return x;
            }
            if (index == 1)
            {
                return y;
            }
            if (index == 2)
            {
                return z;
            }
            return 0;
        }

        static Vec3D<T> reflect(Vec3D<T> in, Vec3D<T> normal)
        {
            return (in - (normal * 2.f * in.dot(normal)));
        }
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &output, const Vec3D<T> &t1)
    {
        //output << "x: " << t1.x << " y: " << t1.y << " z: " << t1.z << std::endl;
        output << t1.x << "," << t1.y << "," << t1.z;
        return output;
    }

    template <typename T>
    Vec3D<T> operator+(const Vec3D<T> &t1, const Vec3D<T> &t2)
    {
        T new_x = t1.x + t2.x;
        T new_y = t1.y + t2.y;
        T new_z = t1.z + t2.z;

        Vec3D<T> sum{ new_x, new_y, new_z};
        return sum;
    }

    template <typename T>
    Vec3D<T> operator-(const Vec3D<T> &t1, const Vec3D<T> &t2)
    {
        T x = t1.x - t2.x;
        T y = t1.y - t2.y;
        T z = t1.z - t2.z;

        Vec3D<T> diff = {x, y, z};
        return diff;
    }

    template <typename T>
    Vec3D<T> operator-(const Vec3D<T> &t1)
    {
        Vec3D<T> zero = {0, 0, 0};
        Vec3D<T> neg = zero - t1;
        return neg;
    }

    template <typename T>
    Vec3D<T> operator*(const Vec3D<T> &t1, const T &multiplier)
    {
        T x = t1.x * multiplier;
        T y = t1.y * multiplier;
        T z = t1.z * multiplier;

        Vec3D<T> product = {x, y, z};
        return product;
    }

    template <typename T>
    Vec3D<T> operator/(const Vec3D<T> &t1, const T &divisor)
    {
        T x = t1.x / divisor;
        T y = t1.y / divisor;
        T z = t1.z / divisor;

        Vec3D<T> div = {x, y, z};
        return div;
    }
} // namespace Ray_Tracer
