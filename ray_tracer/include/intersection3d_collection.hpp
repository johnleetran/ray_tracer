#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <optional>
#include <vector>
#include "intersection3d.hpp"


#pragma once
    namespace Ray_Tracer
{
    template <typename T>
    class Intersection3D_Collection
    {
    public:
        T inf = std::numeric_limits<T>::infinity();
        std::vector<Intersection3D<T>> collection;
        Intersection3D_Collection() {}
        Intersection3D<T> add(Intersection3D<T> inter)
        {
            collection.push_back(inter);
            return inter;
        }

        Intersection3D<T> get(int index){
            return collection[index];
        }

        std::optional<Intersection3D<T>> get_hit(){
            T t_min = inf;
            std::optional < Intersection3D<T> > min_hit;
            for (auto &inter : collection)
            {
                if (inter.t > 0 && inter.t < t_min)
                {
                    min_hit = inter;
                    t_min = inter.t;
                }
            }
            if (min_hit)
            {
                return { min_hit } ;
            }
            else
            {
                return std::nullopt;
            }
        }
    };
} // namespace Ray_Tracer