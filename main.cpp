#include <iostream>
#include <vector>
#include <cmath>
#include <thread>

#include "canvas3d.hpp"
#include "color3d.hpp"
#include "intersection3d.hpp"
#include "intersection3d_collection.hpp"
#include "material3d.hpp"
#include "matrix3d.hpp"
#include "point_light3d.hpp"
#include "ray3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"
#include "vec3d.hpp"

struct Projectile 
{
    Ray_Tracer::Vec3D<float> position;
    Ray_Tracer::Vec3D<float> velocity;
};

struct Evnironment
{
    Ray_Tracer::Vec3D<float> gravity;
    Ray_Tracer::Vec3D<float> wind;
};

struct my_color{
    int r;
    int g;
    int b;
};

Projectile tick(Projectile projectile, Evnironment env)
{
    Ray_Tracer::Vec3D<float> new_position = projectile.position + projectile.velocity;
    Ray_Tracer::Vec3D<float> new_velocity = projectile.velocity + env.gravity + env.wind;
    Projectile proj = {new_position, new_velocity};
    return proj;
}

int projectile_program(){
    Ray_Tracer::Vec3D<float> position{0.f, 1.f, 0.f};
    Ray_Tracer::Vec3D<float> velocity{1.f, 1.8f, 0.f};
    Projectile proj = {
        position,
        velocity.normalize() * 11.25f};

    Evnironment env = {
        Ray_Tracer::Vec3D<float>{0.f, -0.1f, 0.f},
        Ray_Tracer::Vec3D<float>{-0.01f, 0.f, 0.f}};

    int width = 900;
    int height = 550;
    Ray_Tracer::Canvas3d canvas{width, height};

    Projectile p = proj;
    float x = 0;
    float y = 0;
    while (p.position.y >= 0.0 && p.position.y < height && p.position.x < width)
    {
        Ray_Tracer::Color3D<float> tmp_color{1.f, 1.f, 1.f};
        canvas.write_pixels(p.position.x, p.position.y, tmp_color);
        std::cout << p.position << std::endl;
        p = tick(p, env);
    }
    canvas.canvas_to_ppm("./image.ppm");
    return 0;
}

int render_sphere(){
    int width = 100;
    int height = 100;
    Ray_Tracer::Canvas3d canvas{width, height};

    Ray_Tracer::Color3D<float> red{1.f, 0,0};
    Ray_Tracer::Color3D<float> white{1.f, 1.f, 1.f};
    Ray_Tracer::Color3D<float> black{0.f, 0.f, 0.f};

    std::string uuid1 = "sphere";
    Ray_Tracer::Sphere3D<float> sphere{1.f, uuid1};
    Ray_Tracer::Matrix3D<float> transform_matrix = sphere.get_transform();
    transform_matrix = transform_matrix.translate(1.f, 1.0, .0);
    sphere.transform(transform_matrix);

    float wall_z = 10;
    float wall_size = 7.f;
    float half = wall_size / 2.f;
    float pixel_size = wall_size / width;

    Ray_Tracer::Tuple3D<float> ray_origin{0, 0, -5};
    Ray_Tracer::Vec3D<float> ray_direction{0, 0, 1};

    Ray_Tracer::Intersection3D_Collection<float> intersection_collection{};

    for (int y = 0; y < height; y++)
    {
        float world_y = half - pixel_size * y;
        for(int x = 0; x < width; x++){
            float world_x = -half + pixel_size * x;
            //Ray_Tracer::Tuple3D<float> position { world_x, world_y, wall_z};
            Ray_Tracer::Vec3D<float> position{
                static_cast<float>(world_x), 
                static_cast<float>(world_y), 
                static_cast<float>(wall_z)
            };

            Ray_Tracer::Vec3D<float> ray_direction = position - Ray_Tracer::Vec3D<float> {ray_origin.x, ray_origin.y, ray_origin.z};
            Ray_Tracer::Ray3D<float> ray{ray_origin, ray_direction.normalize()};

            std::optional<std::vector<float>> intersection_points = Ray_Tracer::Intersection3D<float>::intersect(ray, sphere);
            if (x % 50 == 0){
                std::cout << "x: " << x << " y: " << y << std::endl;
            }
            if (intersection_points){
                Ray_Tracer::Intersection3D<float> intersection{intersection_points->at(0), sphere};
                intersection_collection.add(intersection);
                if (intersection_collection.get_hit())
                {
                    canvas.write_pixels(x, y, red);
                }
            }
        }
    }
    canvas.canvas_to_ppm("./image.ppm");
    return 0;
}

int render_sphere_with_lights(Ray_Tracer::Canvas3d *canvas, int width, int height, int from_x, int to_x, int from_y, int to_y)
{
    Ray_Tracer::Color3D<float> red{1.f, 0, 0};
    Ray_Tracer::Color3D<float> white{1.f, 1.f, 1.f};
    Ray_Tracer::Color3D<float> black{0.f, 0.f, 0.f};

    std::string uuid1 = "sphere";
    Ray_Tracer::Sphere3D<float> sphere{1.f, uuid1};
    Ray_Tracer::Matrix3D<float> transform_matrix = sphere.get_transform();

    //add material to sphere
    sphere.material = Ray_Tracer::Material3D<float>{};
    sphere.material.color = Ray_Tracer::Color3D<float>{1, 0.2, 1};
    // transform_matrix = transform_matrix.translate(1.f, 1.0, .0);
    // sphere.transform(transform_matrix);

    //add light source
    Ray_Tracer::Tuple3D<float> light_position{-10, 10, -10};
    Ray_Tracer::Color3D<float> intensity{1, 1, 1};
    Ray_Tracer::PointLight3D<float> light{light_position, intensity};

    float wall_z = 10;
    float wall_size = 7.f;
    float half = wall_size / 2.f;
    float pixel_size = wall_size / width;

    Ray_Tracer::Tuple3D<float> ray_origin{0, 0, -5};
    Ray_Tracer::Vec3D<float> ray_direction{0, 0, 1};

    Ray_Tracer::Intersection3D_Collection<float> intersection_collection{};

    for (int y = from_y; y < to_y; y++)
    {
        float world_y = half - pixel_size * y;
        for (int x = from_x; x < to_x; x++)
        {
            float world_x = -half + pixel_size * x;
            //Ray_Tracer::Tuple3D<float> position { world_x, world_y, wall_z};
            Ray_Tracer::Vec3D<float> position{
                static_cast<float>(world_x),
                static_cast<float>(world_y),
                static_cast<float>(wall_z)};

            Ray_Tracer::Vec3D<float> ray_direction = position - Ray_Tracer::Vec3D<float>{ray_origin.x, ray_origin.y, ray_origin.z};
            Ray_Tracer::Ray3D<float> ray{ray_origin, ray_direction.normalize()};

            std::optional<std::vector<float>> intersection_points = Ray_Tracer::Intersection3D<float>::intersect(ray, sphere);
            if (x % 50 == 0)
            {
                std::cout << "x: " << x << " y: " << y << std::endl;
            }
            if (intersection_points)
            {
                Ray_Tracer::Intersection3D<float> intersection{intersection_points->at(0), sphere};
                intersection_collection.add(intersection);
                if (intersection_collection.get_hit())
                {
                    std::optional<Ray_Tracer::Intersection3D<float>> hit = intersection_collection.get_hit();
                    Ray_Tracer::Tuple3D<float> point = ray.position(hit->t);
                    Ray_Tracer::Vec3D<float> normal = hit->object.normalize_at(point);
                    Ray_Tracer::Vec3D<float> eye = -ray.direction;
                    Ray_Tracer::Color3D<float> color = Ray_Tracer::Material3D<float>::lighting(hit->object.material, light, point, eye, normal);
                    canvas->write_pixels(x, y, color);
                }
            }
        }
    }
    return 0;
}

int render_sphere_with_lights_threads()
{
    const auto processor_count = std::thread::hardware_concurrency();

    int width = 100;
    int height = 100;
    Ray_Tracer::Canvas3d canvas{width, height};

    std::thread t1{render_sphere_with_lights, &canvas, width, height, 0, width, 0,   50};
    std::thread t2{render_sphere_with_lights, &canvas, width, height, 0, width, 50,  100};
    std::thread t3{render_sphere_with_lights, &canvas, width, height, 0, width, 100, 150};
    std::thread t4{render_sphere_with_lights, &canvas, width, height, 0, width, 150, 200};

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    //render_sphere_with_lights(&canvas, width, height, 0, width, 0, height);

    canvas.canvas_to_ppm("./image.ppm");

    return 0;

    // render_sphere_with_lights(width, height, 0, width, 50, 99);
    // render_sphere_with_lights(width, height, 0, width, 100, 149);
    // render_sphere_with_lights(width, height, 0, width, 150, 199);
}

int main(int argc, char *argv[])
{
    //may return 0 when not able to detect
    //return projectile_program();
    //return render_sphere();
    return render_sphere_with_lights_threads();
}