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

using namespace Ray_Tracer;

struct Projectile 
{
    Vec3D<float> position;
    Vec3D<float> velocity;
};

struct Evnironment
{
    Vec3D<float> gravity;
    Vec3D<float> wind;
};

struct my_color{
    int r;
    int g;
    int b;
};

Projectile tick(Projectile projectile, Evnironment env)
{
    Vec3D<float> new_position = projectile.position + projectile.velocity;
    Vec3D<float> new_velocity = projectile.velocity + env.gravity + env.wind;
    Projectile proj = {new_position, new_velocity};
    return proj;
}

int projectile_program(){
    Vec3D<float> position{0.f, 1.f, 0.f};
    Vec3D<float> velocity{1.f, 1.8f, 0.f};
    Projectile proj = {
        position,
        velocity.normalize() * 11.25f};

    Evnironment env = {
        Vec3D<float>{0.f, -0.1f, 0.f},
        Vec3D<float>{-0.01f, 0.f, 0.f}};

    float width = 900;
    float height = 550;
    Canvas3D<float> canvas{width, height};

    Projectile p = proj;
    float x = 0;
    float y = 0;
    while (p.position.y >= 0.0 && p.position.y < height && p.position.x < width)
    {
        Color3D<float> tmp_color{1.f, 1.f, 1.f};
        canvas.write_pixels(p.position.x, p.position.y, tmp_color);
        std::cout << p.position << std::endl;
        p = tick(p, env);
    }
    canvas.canvas_to_ppm("./image.ppm");
    return 0;
}

int render_sphere(){
    float width = 100;
    float height = 100;
    Canvas3D<float> canvas{width, height};

    Color3D<float> red{1.f, 0,0};
    Color3D<float> white{1.f, 1.f, 1.f};
    Color3D<float> black{0.f, 0.f, 0.f};

    std::string uuid1 = "sphere";
    Sphere3D<float> sphere{1.f, uuid1};
    Matrix3D<float> transform_matrix = sphere.get_transform();
    transform_matrix = transform_matrix.translate(1.f, 1.0, .0);
    sphere.transform(transform_matrix);

    float wall_z = 10;
    float wall_size = 7.f;
    float half = wall_size / 2.f;
    float pixel_size = wall_size / width;

    Tuple3D<float> ray_origin{0, 0, -5};
    Vec3D<float> ray_direction{0, 0, 1};

    Intersection3D_Collection<float> intersection_collection{};

    for (int y = 0; y < height; y++)
    {
        float world_y = half - pixel_size * y;
        for(int x = 0; x < width; x++){
            float world_x = -half + pixel_size * x;
            //Tuple3D<float> position { world_x, world_y, wall_z};
            Vec3D<float> position{
                static_cast<float>(world_x), 
                static_cast<float>(world_y), 
                static_cast<float>(wall_z)
            };

            Vec3D<float> ray_direction = position - Vec3D<float> {ray_origin.x, ray_origin.y, ray_origin.z};
            Ray3D<float> ray{ray_origin, ray_direction.normalize()};

            std::optional<std::vector<float>> intersection_points = Intersection3D<float>::intersect(ray, sphere);
            if (x % 50 == 0){
                std::cout << "x: " << x << " y: " << y << std::endl;
            }
            if (intersection_points){
                Intersection3D<float> intersection{intersection_points->at(0), sphere};
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

int render_sphere_with_lights(Canvas3D<float> *canvas, float width, float height, int from_x, int to_x, int from_y, int to_y)
{
    Color3D<float> red{1.f, 0, 0};
    Color3D<float> white{1.f, 1.f, 1.f};
    Color3D<float> black{0.f, 0.f, 0.f};

    std::string uuid1 = "sphere";
    Sphere3D<float> sphere{1.f, uuid1};
    Matrix3D<float> transform_matrix = sphere.get_transform();

    //add material to sphere
    sphere.material = Material3D<float>{};
    sphere.material.color = Color3D<float>{1, 0.2, 1};
    // transform_matrix = transform_matrix.translate(1.f, 1.0, .0);
    // sphere.transform(transform_matrix);

    //add light source
    Tuple3D<float> light_position{-10, 10, -10};
    Color3D<float> intensity{1, 1, 1};
    PointLight3D<float> light{light_position, intensity};

    float wall_z = 10;
    float wall_size = 7.f;
    float half = wall_size / 2.f;
    float pixel_size = wall_size / width;

    Tuple3D<float> ray_origin{0, 0, -5};
    Vec3D<float> ray_direction{0, 0, 1};

    Intersection3D_Collection<float> intersection_collection{};

    for (int y = from_y; y < to_y; y++)
    {
        float world_y = half - pixel_size * y;
        for (int x = from_x; x < to_x; x++)
        {
            float world_x = -half + pixel_size * x;
            //Tuple3D<float> position { world_x, world_y, wall_z};
            Vec3D<float> position{
                static_cast<float>(world_x),
                static_cast<float>(world_y),
                static_cast<float>(wall_z)};

            Vec3D<float> ray_direction = position - Vec3D<float>{ray_origin.x, ray_origin.y, ray_origin.z};
            Ray3D<float> ray{ray_origin, ray_direction.normalize()};

            std::optional<std::vector<float>> intersection_points = Intersection3D<float>::intersect(ray, sphere);
            if (x % 50 == 0)
            {
                std::cout << "x: " << x << " y: " << y << std::endl;
            }
            if (intersection_points)
            {
                Intersection3D<float> intersection{intersection_points->at(0), sphere};
                intersection_collection.add(intersection);
                if (intersection_collection.get_hit())
                {
                    std::optional<Intersection3D<float>> hit = intersection_collection.get_hit();
                    Tuple3D<float> point = ray.position(hit->t);
                    Vec3D<float> normal = hit->object.normal_at(point);
                    Vec3D<float> eye = -ray.direction;
                    Color3D<float> color = Material3D<float>::lighting(hit->object.material, light, point, eye, normal, false);
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

    float width = 100;
    float height = 100;
    Canvas3D<float> canvas{width, height};

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

int render_room_with_sphere()
{
    float width = 50;
    float height = 25;

    //floor
    Sphere3D<float> floor{1.f, "floor"};
    Matrix3D<float> transform_floor = floor.get_transform().scaling(10, 0.01, 10);
    floor.material.color = Color3D<float>{1, 0.9, 0.9};
    floor.material.specular = 0;
    floor.transform(transform_floor);

    //left wall
    Sphere3D<float> left_wall{1.f, "left_wall"};
    Matrix3D<float> transform_left_wall = left_wall.get_transform().translate(0, 0, 5) * left_wall.get_transform().rotation_y(-3.14 / 4.f) * left_wall.get_transform().rotation_x(3.14 / 2.f) * left_wall.get_transform().scaling(10, 0.01, 10);
    left_wall.material = floor.material;
    left_wall.transform(transform_left_wall);

    //right wall
    Sphere3D<float> right_wall{1.f, "right_wall"};
    Matrix3D<float> transform_right_wall = right_wall.get_transform().translate(0, 0, 5) * right_wall.get_transform().rotation_y(3.14 / 4.f) * right_wall.get_transform().rotation_x(3.14 / 2.f) * right_wall.get_transform().scaling(10, 0.01, 10);
    right_wall.material = floor.material;
    right_wall.transform(transform_right_wall);

    //middle sphere
    Sphere3D<float> middle_sphere{1.f, "middle_sphere"};
    Matrix3D<float> transform_middle_sphere = middle_sphere.get_transform().translate(-0.5, 1, 0.5);
    middle_sphere.material.color = Color3D<float>{0.1, 1.f, 0.5};
    middle_sphere.material.diffuse = 0.7;
    middle_sphere.material.specular = 0.3;
    middle_sphere.transform(transform_middle_sphere);

    //right sphere
    Sphere3D<float> right_sphere{1.f, "right_sphere"};
    Matrix3D<float> transform_right_sphere = right_sphere.get_transform().translate(1.5, 0.5, -0.5) * right_sphere.get_transform().scaling(0.5, 0.5, 0.5);
    right_sphere.material.color = Color3D<float>{0.5, 1, 0.1};
    right_sphere.material.diffuse = 0.7;
    right_sphere.material.specular = 0.3;
    right_sphere.transform(transform_right_sphere);

    //left sphere
    Sphere3D<float> left_sphere{1.f, "left_sphere"};
    Matrix3D<float> transform_left_sphere = left_sphere.get_transform().translate(-1.5, 0.33, -0.75) * left_sphere.get_transform().scaling(0.33, 0.33, 0.33);
    left_sphere.material.color = Color3D<float>{1, 0.8, 0.1};
    left_sphere.material.diffuse = 0.7;
    left_sphere.material.specular = 0.3;
    left_sphere.transform(transform_left_sphere);

    Tuple3D<float> light_position{-10, 10, -10};
    Color3D<float> light_color{1, 1, 1};
    PointLight3D<float> light{light_position, light_color};

    World3D<float> w{};
    w.light = light;
    w.clear_objects();
    w.objects.push_back(floor);
    w.objects.push_back(left_wall);
    w.objects.push_back(right_wall);
    w.objects.push_back(middle_sphere);
    w.objects.push_back(right_sphere);
    w.objects.push_back(left_sphere);

    Camera3D<float> c(width, height, 3.14 / 3.f);
    Tuple3D<float> from{0, 1.5, -5};
    Tuple3D<float> to{0, 1, 0};
    Vec3D<float> up{0, 1, 0};
    c.transform_matrix = Camera3D<float>::view_transform(from, to, up);

    Canvas3D<float> canvas{width, height};

    canvas.render(c, w);
    canvas.canvas_to_ppm("./image-main.ppm");
    return 0;
}

int main(int argc, char *argv[])
{
    //may return 0 when not able to detect
    //return projectile_program();
    //return render_sphere();
    //return render_sphere_with_lights_threads();

    return render_room_with_sphere();
}