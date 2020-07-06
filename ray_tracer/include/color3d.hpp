#include <cmath>
#include <iostream>

#include "../include/vec3d.hpp"
#pragma once

namespace Ray_Tracer
{
    namespace Color3D
    {
        template<typename T> 
        class Color3D{
            public:
            T r;
            T g;
            T b;

            Color3D() : r(0.0f), g(0.0f), b(0.0f) {}

            Color3D(T r, T g, T b) : r(r), g(g), b(b) {  }

            Color3D<T> scale(T multiplier)
            {
                T new_r = r * multiplier;
                T new_g = g * multiplier;
                T new_b = b * multiplier;

                Color3D<T> c{new_r, new_g, new_b};
                return c;
            }
        };

        template <typename T>
        Color3D<T> operator+(const Color3D<T> &t1, const Color3D<T> &t2)
        {
            T new_r = t1.r + t2.r;
            T new_g = t1.g + t2.g;
            T new_b = t1.b + t2.b;

            Color3D<T> c{new_r, new_g, new_b};
            return c;
        }

        template <typename T>
        Color3D<T> operator-(const Color3D<T> &t1, const Color3D<T> &t2)
        {
            T new_r = t1.r - t2.r;
            T new_g = t1.g - t2.g;
            T new_b = t1.b - t2.b;

            Color3D<T> c{new_r, new_g, new_b};
            return c;
        }

        template <typename T>
        Color3D<T> operator*(const Color3D<T> &t1, const Color3D<T> &t2)
        {
            T new_r = t1.r * t2.r;
            T new_g = t1.g * t2.g;
            T new_b = t1.b * t2.b;

            Color3D<T> c{new_r, new_g, new_b};
            return c;
        }
    }
}