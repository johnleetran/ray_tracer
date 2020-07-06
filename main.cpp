#include <iostream>
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

Projectile tick(Projectile projectile, Evnironment env)
{
    Ray_Tracer::Vec3D::Vec3D<float> new_position = projectile.position + projectile.velocity;
    Ray_Tracer::Vec3D::Vec3D<float> new_velocity = projectile.velocity + env.gravity;
    new_velocity = new_velocity + env.wind;
    Projectile proj = {new_position, new_velocity};
    return proj;
}

int main(int argc, char *argv[])
{
    Ray_Tracer::Vec3D::Vec3D<float> position{0.f, 1.f, 0.f};
    Ray_Tracer::Vec3D::Vec3D<float> velocity{1.f, 1.f, 0.f};
    Projectile proj = {
        position,
        velocity.normalize()
    };

    Evnironment env = {
        Ray_Tracer::Vec3D::Vec3D<float>{0.f, -0.1f, 0.f},
        Ray_Tracer::Vec3D::Vec3D<float>{-0.01f, 0.f, 0.f}};

    std::string x;
    Projectile p = proj;
    while (std::cin >> x)
    {
        if (x == "q")
        {
            break;
        }
        p = tick(p, env);
        std::cout << "x: " << p.position << std::endl;
    }
    return 0;
}