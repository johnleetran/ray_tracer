#include <iostream>
#include "vec3d_utils.hpp"

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
    Ray_Tracer::Vec3D::Vec3D<float> new_position = Ray_Tracer::Vec3D::add<float>(projectile.position, projectile.velocity);
    Ray_Tracer::Vec3D::Vec3D<float> new_velocity = Ray_Tracer::Vec3D::add<float>(projectile.velocity, env.gravity);
    new_velocity = Ray_Tracer::Vec3D::add<float>(new_velocity, env.wind);
    Projectile proj = {new_position, new_velocity};
    return proj;
}

int main(int argc, char *argv[])
{
    Projectile proj = {
        {0.f, 1.f, 0.f},
        {Ray_Tracer::Vec3D::normalize<float>({1.f, 1.f, 0.f})}};

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
        std::cout << "x: " << p.position.x << " y: " << p.position.y << " z: " << p.position.z << std::endl;
    }
    return 0;
}