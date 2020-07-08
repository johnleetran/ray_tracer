#include "./color3d.hpp"
#include "./point_light3d.hpp"
#include "./tuple3d.hpp"
#include "./vec3d.hpp"

#pragma once
namespace Ray_Tracer
{
    template <typename T>
    class Material3D
    {
    public:
        Ray_Tracer::Color3D<T> color {1,1,1};
        float ambient = 0.1;
        float diffuse = 0.9;
        float specular = 0.9;
        float shininess = 200.0;
        Material3D() {}

        static Ray_Tracer::Color3D<T> lighting(
            Material3D<T> material,
            Ray_Tracer::PointLight3D<T> light,
            Ray_Tracer::Tuple3D<T> point,
            Ray_Tracer::Vec3D<T> eyev,
            Ray_Tracer::Vec3D<T> normalv)
        {

            Ray_Tracer::Color3D<T> effective_color = material.color * light.intensity;
            Ray_Tracer::Tuple3D<T> diff_point = (light.position - point);
            Ray_Tracer::Vec3D<T> diff_point_vector{diff_point.x, diff_point.y, diff_point.z};
            Ray_Tracer::Vec3D<T> lightv = diff_point_vector.normalize();
            Ray_Tracer::Color3D<T> ambient = effective_color * material.ambient;
            float light_dot_normal = lightv.dot(normalv);
            Ray_Tracer::Color3D<T> diffuse{};
            Ray_Tracer::Color3D<T> specular{};
            if (light_dot_normal < 0)
            {
                diffuse = Ray_Tracer::Color3D<T>{0.0f, 0.0f, 0.0f};
                specular = Ray_Tracer::Color3D<T>{0.0f, 0.0f, 0.0f};
            }
            else
            {
                diffuse = effective_color * material.diffuse * light_dot_normal;
                Ray_Tracer::Vec3D<T> reflectv = Ray_Tracer::Vec3D<T>::reflect(-lightv, normalv);
                float reflect_dot_eye = reflectv.dot(eyev);
                if (reflect_dot_eye <= 0)
                {
                    specular = Ray_Tracer::Color3D<T>{0.0f, 0.0f, 0.0f};
                }
                else
                {
                    float factor = std::pow(reflect_dot_eye, material.shininess);
                    specular = light.intensity * material.specular * factor;
                }
            }
            Ray_Tracer::Color3D<float> c = ambient + diffuse + specular;
            return c;
        }
    };
} // namespace Ray_Tracer