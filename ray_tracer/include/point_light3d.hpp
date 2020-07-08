#include "./color3d.hpp"
#include "./material3d.hpp"
#include "./vec3d.hpp"
#include "./tuple3d.hpp"

#pragma once
namespace Ray_Tracer{
    template<typename T>
    class PointLight3D{
        public:
        Ray_Tracer::Color3D::Color3D<T> intensity;
        Ray_Tracer::Tuple3D::Tuple3D<T> position;
        PointLight3D(Ray_Tracer::Tuple3D::Tuple3D<T> position, Ray_Tracer::Color3D::Color3D<T> intensity) : position(position), intensity(intensity) {}

        static Ray_Tracer::Color3D::Color3D<T> lighting(
            Ray_Tracer::Material3D<T> material,
            PointLight3D light,
            Ray_Tracer::Tuple3D::Tuple3D<T> point,
            Ray_Tracer::Vec3D::Vec3D<T> eyev,
            Ray_Tracer::Vec3D::Vec3D<T> normalv){

                Ray_Tracer::Color3D::Color3D<T> effective_color = material.color * light.intensity;
                Ray_Tracer::Tuple3D::Tuple3D<T> diff_point = (light.position - point);
                Ray_Tracer::Vec3D::Vec3D<T> diff_point_vector{diff_point.x, diff_point.y, diff_point.z};
                Ray_Tracer::Vec3D::Vec3D<T> lightv = diff_point_vector.normalize();
                float ambient = effective_color.r * material.ambient;
                float light_dot_normal = lightv.dot(normalv);
                float diffuse = 0.0f;
                float specular = 0.0f;
                if(light_dot_normal < 0){
                    diffuse = 0.0f;
                    specular = 0.0f;
                }else{
                    diffuse = effective_color.r * material.diffuse * light_dot_normal;
                    Ray_Tracer::Vec3D::Vec3D<T> reflectv = Ray_Tracer::Vec3D::Vec3D<T>::reflect(-lightv, normalv);
                    float reflect_dot_eye = reflectv.dot(eyev);
                    if(reflect_dot_eye <= 0){
                        specular = 0.0f;
                    }else{
                        float factor = std::pow(reflect_dot_eye, material.shininess);
                        specular = light.intensity.r * material.specular * factor;
                    }
                }
                float c = ambient + diffuse + specular;
                Ray_Tracer::Color3D::Color3D<float> return_color{c,c,c};
                return return_color;
            }
    };
}