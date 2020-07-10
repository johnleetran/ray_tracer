#include "color3d.hpp"
#include "comps3d.hpp"
#include "intersection3d.hpp"
#include "intersection3d_collection.hpp"

#include "material3d.hpp"
#include "matrix3d.hpp"
#include "point_light3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"

#pragma once
using namespace Ray_Tracer;

namespace Ray_Tracer
{
    template <typename T>
    class World3D{
        public:
            PointLight3D<T> light;
            std::vector<Sphere3D<T>> objects;
            World3D(){
                //default light
                light = PointLight3D<T>{Tuple3D<T>{-10, 10, -10},
                                         Color3D<T>{1, 1, 1}};

                //default object
                Sphere3D<T> sphere1{1, "defaultObject1"};
                sphere1.material.color = Color3D<T>{0.8, 1.0, 0.6};
                sphere1.material.diffuse = 0.7;
                sphere1.material.specular = 0.2;
                objects.push_back(sphere1);

                Sphere3D<T> sphere2{1, "defaultObject2"};
                Matrix3D<T> tranform_matrix = sphere2.get_transform();
                tranform_matrix = tranform_matrix.scaling(0.5, 0.5, 0.5);
                sphere2.transform(tranform_matrix);
                objects.push_back(sphere2);
            }

            Intersection3D_Collection<T> intersect_world(Ray3D<T> ray)
            {
                Intersection3D_Collection<T> intersection_collection;

                for(auto obj : objects){
                    std::optional<std::vector<float>> intersection_points = Ray_Tracer::Intersection3D<float>::intersect(ray, obj);
                    if(intersection_points){
                        Ray_Tracer::Intersection3D<float> intersection0{intersection_points->at(0), obj};
                        intersection_collection.add(intersection0);
                        Ray_Tracer::Intersection3D<float> intersection1{intersection_points->at(1), obj};
                        intersection_collection.add(intersection1);
                    }
                }
                intersection_collection.sort();
                return intersection_collection;
            }

            static Comps3D<T> prepare_computations(Intersection3D<T> intersection, Ray3D<T> ray){
                Comps3D<T> comps{};
                comps.t = intersection.t;
                comps.object = intersection.object;
                comps.point = ray.position(comps.t);
                comps.eyev = -ray.direction;
                comps.normalv = comps.object.normal_at(comps.point);
                if(comps.normalv.dot(comps.eyev) < 0){
                    comps.inside = true;
                    comps.normalv = -comps.normalv;
                }else{
                    comps.inside = false;
                }

                T epsilon = 0.01;
                //std::numeric_limits<T>::epsilon();
                comps.over_point = comps.point + comps.normalv * epsilon;
                return comps;
            }

            Color3D<T> shade_hit(Comps3D<T> comps){
                bool in_shadow = is_shadowed(comps.over_point);
                Color3D<T> lighting = Material3D<T>::lighting(
                    comps.object.material,
                    light,
                    comps.point,
                    comps.eyev,
                    comps.normalv,
                    in_shadow);
                return lighting;
            }

            Color3D<T> color_at(Ray3D<T> ray){
                Color3D<T> the_color{0,0,0};
                Intersection3D_Collection<T> inter_collection = intersect_world(ray);
                std::optional<Intersection3D<T>> hit = inter_collection.get_hit();
                if(hit){
                    Comps3D<T> comps = prepare_computations(*hit, ray);
                    the_color = shade_hit(comps);
                }   

                return the_color;
            }

            void clear_objects(){
                objects.clear();
            }

            bool is_shadowed(Tuple3D<T> point){
                Tuple3D<T> v = light.position - point;
                float distance = v.magnitude();
                Vec3D<T> direction{v.normalize().x, v.normalize().y, v.normalize().z};

                Ray3D<T> r { point, direction };
                Intersection3D_Collection<T> inter_collection = intersect_world(r);
                std::optional<Intersection3D<T>> hit = inter_collection.get_hit();
                if (hit && hit->t < distance){
                    return true;
                }else{
                    return false;
                }
            }
    };
}