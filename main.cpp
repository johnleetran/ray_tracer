#include <iostream>
#include <vector>
#include <cmath>

#include "canvas3d.hpp"
#include "color3d.hpp"
#include "intersection3d.hpp"
#include "intersection3d_collection.hpp"
#include "matrix3d.hpp"
#include "ray3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"
#include "vec3d.hpp"

struct Projectile 
{
    Ray_Tracer::Vec3D::Vec3D<float> position;
    Ray_Tracer::Vec3D::Vec3D<float> velocity;
};

struct Evnironment
{
    Ray_Tracer::Vec3D::Vec3D<float> gravity;
    Ray_Tracer::Vec3D::Vec3D<float> wind;
};

struct my_color{
    int r;
    int g;
    int b;
};

Projectile tick(Projectile projectile, Evnironment env)
{
    Ray_Tracer::Vec3D::Vec3D<float> new_position = projectile.position + projectile.velocity;
    Ray_Tracer::Vec3D::Vec3D<float> new_velocity = projectile.velocity + env.gravity + env.wind;
    Projectile proj = {new_position, new_velocity};
    return proj;
}

int projectile_program(){
    Ray_Tracer::Vec3D::Vec3D<float> position{0.f, 1.f, 0.f};
    Ray_Tracer::Vec3D::Vec3D<float> velocity{1.f, 1.8f, 0.f};
    Projectile proj = {
        position,
        velocity.normalize() * 11.25f};

    Evnironment env = {
        Ray_Tracer::Vec3D::Vec3D<float>{0.f, -0.1f, 0.f},
        Ray_Tracer::Vec3D::Vec3D<float>{-0.01f, 0.f, 0.f}};

    int width = 900;
    int height = 550;
    Ray_Tracer::Canvas3d::Canvas3d canvas{width, height};

    Projectile p = proj;
    float x = 0;
    float y = 0;
    while (p.position.y >= 0.0 && p.position.y < height && p.position.x < width)
    {
        Ray_Tracer::Color3D::Color3D<float> tmp_color{1.f, 1.f, 1.f};
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
    Ray_Tracer::Canvas3d::Canvas3d canvas{width, height};

    Ray_Tracer::Color3D::Color3D<float> red{1.f, 0,0};
    Ray_Tracer::Color3D::Color3D<float> white{1.f, 1.f, 1.f};
    Ray_Tracer::Color3D::Color3D<float> black{0.f, 0.f, 0.f};

    std::string uuid1 = "sphere";
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.f, uuid1};
    //sphere.transform(scaling_matrix);

    float wall_z = 10;
    float wall_size = 7.f;
    float half = wall_size / 2.f;
    float pixel_size = wall_size / width;

    Ray_Tracer::Tuple3D::Tuple3D<float> ray_origin{0, 0, -5};
    Ray_Tracer::Vec3D::Vec3D<float> ray_direction{0, 0, 1};

    Ray_Tracer::Intersection3D_Collection<float> intersection_collection{};

    for (int y = 0; y < height; y++)
    {
        float world_y = half - pixel_size * y;
        for(int x = 0; x < width; x++){
            float world_x = -half + pixel_size * x;
            //Ray_Tracer::Tuple3D::Tuple3D<float> position { world_x, world_y, wall_z};
            Ray_Tracer::Vec3D::Vec3D<float> position{
                static_cast<float>(world_x), 
                static_cast<float>(world_y), 
                static_cast<float>(wall_z)
            };

            Ray_Tracer::Vec3D::Vec3D<float> ray_direction = position - Ray_Tracer::Vec3D::Vec3D<float> {ray_origin.x, ray_origin.y, ray_origin.z};
            Ray_Tracer::Ray3D::Ray3D<float> ray{ray_origin, ray_direction.normalize()};

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
                else
                {
                    canvas.write_pixels(x, y, white);
                }
            }
  
            //}else{
            //    canvas.write_pixels(x, y, black);
            //}

            // std::optional<std::vector<float>> intersection_points = Ray_Tracer::Intersection3D<float>::intersect(ray, sphere);
            // if (intersection_points){
            //     canvas.write_pixels(static_cast<int>(x), 0, tmp_color);
            // }
            // // EXPECT_NEAR(intersection_points->at(0), -1.0, 0.0001);
            // // EXPECT_NEAR(intersection_points->at(1), 1.0, 0.0001);
        }
    }
    canvas.canvas_to_ppm("./image.ppm");
    return 0;
}

int main(int argc, char *argv[])
{
    //return projectile_program();

    return render_sphere();
}