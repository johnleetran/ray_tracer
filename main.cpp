#include <iostream>
#include <vector>
#include <cmath>

#include "canvas3d.hpp"
#include "color3d.hpp"
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

int main(int argc, char *argv[])
{
    Ray_Tracer::Vec3D::Vec3D<float> position{0.f, 1.f, 0.f};
    Ray_Tracer::Vec3D::Vec3D<float> velocity{1.f, 1.8f, 0.f};
    Projectile proj = {
        position,
        velocity.normalize() * 11.25f
    };

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