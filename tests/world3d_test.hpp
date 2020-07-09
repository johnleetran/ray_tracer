#include <gtest/gtest.h> // googletest header file

#include <string>
#include <cmath>

#include "color3d.hpp"
#include "intersection3d.hpp"
#include "intersection3d_collection.hpp"
#include "material3d.hpp"
#include "point_light3d.hpp"
#include "ray3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"
#include "util3d.hpp"
#include "vec3d.hpp"
#include "world3d.hpp"

using namespace Ray_Tracer;

TEST(World3D, TheDefaultWorld)
{
    World3D<float> world{};
    PointLight3D<float> light {Tuple3D<float>{-10, 10, -10}, Color3D<float>{1, 1, 1}};
    EXPECT_NEAR(light.intensity.r, world.light.intensity.r, 0.0001);
    EXPECT_NEAR(light.intensity.g, world.light.intensity.g, 0.0001);
    EXPECT_NEAR(light.intensity.b, world.light.intensity.b, 0.0001);

    EXPECT_NEAR(light.position.x, world.light.position.x, 0.0001);
    EXPECT_NEAR(light.position.y, world.light.position.y, 0.0001);
    EXPECT_NEAR(light.position.z, world.light.position.z, 0.0001);

    EXPECT_EQ(world.objects.size(), 2);
}

TEST(World3D, WorldIntersection)
{
    World3D<float> world{};
    Ray3D ray{Tuple3D<float>{0, 0, -5}, Vec3D<float>{0, 0, 1}};
    Intersection3D_Collection<float> intersection_collection = world.intersect_world(ray);
    EXPECT_NEAR(intersection_collection.collection.at(0).t, 4, 0.0001);
    EXPECT_NEAR(intersection_collection.collection.at(1).t, 4.5, 0.0001);
    EXPECT_NEAR(intersection_collection.collection.at(2).t, 5.5, 0.0001);
    EXPECT_NEAR(intersection_collection.collection.at(3).t, 6, 0.0001);
}

TEST(World3D, PrecomputeComps)
{
    World3D<float> world{};
    Ray3D ray{Tuple3D<float>{0, 0, -5}, Vec3D<float>{0, 0, 1}};
    Sphere3D<float> sphere{1.0, "name"};
    Intersection3D<float> intersection(4, sphere);
    Comps3D<float> comps = world.prepare_computations(intersection, ray);

    EXPECT_NEAR(comps.t, intersection.t, 0.0001);

    EXPECT_EQ(comps.object.id, intersection.object.id);

    EXPECT_NEAR(comps.point.x, 0, 0.0001);
    EXPECT_NEAR(comps.point.y, 0, 0.0001);
    EXPECT_NEAR(comps.point.z, -1, 0.0001);

    EXPECT_NEAR(comps.eyev.x, 0, 0.0001);
    EXPECT_NEAR(comps.eyev.y, 0, 0.0001);
    EXPECT_NEAR(comps.eyev.z, -1, 0.0001);

    EXPECT_NEAR(comps.normalv.x, 0, 0.0001);
    EXPECT_NEAR(comps.normalv.y, 0, 0.0001);
    EXPECT_NEAR(comps.normalv.z, -1, 0.0001);

    EXPECT_NEAR(comps.t, intersection.t, 0.0001);

}

TEST(World3D, PrecomputeInsideObject)
{
    World3D<float> world{};
    Ray3D ray{Tuple3D<float>{0, 0, -5}, Vec3D<float>{0, 0, 1}};
    Sphere3D<float> sphere{1.0, "name"};
    Intersection3D<float> intersection(4, sphere);
    Comps3D<float> comps = world.prepare_computations(intersection, ray);

    EXPECT_EQ(comps.inside, false);
}

TEST(World3D, PrecomputeOutsideObject)
{
    World3D<float> world{};
    Ray3D ray{Tuple3D<float>{0, 0, 0}, Vec3D<float>{0, 0, 1}};
    Sphere3D<float> sphere{1.0, "name"};
    Intersection3D<float> intersection(1, sphere);
    Comps3D<float> comps = world.prepare_computations(intersection, ray);

    EXPECT_NEAR(comps.point.x, 0, 0.0001);
    EXPECT_NEAR(comps.point.y, 0, 0.0001);
    EXPECT_NEAR(comps.point.z, 1, 0.0001);

    EXPECT_NEAR(comps.eyev.x, 0, 0.0001);
    EXPECT_NEAR(comps.eyev.y, 0, 0.0001);
    EXPECT_NEAR(comps.eyev.z, -1, 0.0001);

    EXPECT_NEAR(comps.normalv.x, 0, 0.0001);
    EXPECT_NEAR(comps.normalv.y, 0, 0.0001);
    EXPECT_NEAR(comps.normalv.z, -1, 0.0001);

    EXPECT_EQ(comps.inside, true);
}

TEST(World3D, shade_hit1)
{
    World3D<float> world{};
    Ray3D ray{Tuple3D<float>{0, 0, -5}, Vec3D<float>{0, 0, 1}};
    Sphere3D<float> sphere = world.objects[0];//{1.0, "name"};
    Intersection3D<float> intersection(4, sphere);
    Comps3D<float> comps = world.prepare_computations(intersection, ray);

    Color3D<float> shade = world.shade_hit(comps);

    EXPECT_NEAR(shade.r, 0.38066, 0.001);
    EXPECT_NEAR(shade.g, 0.47583, 0.001);
    EXPECT_NEAR(shade.b, 0.2855, 0.001);

    EXPECT_EQ(comps.inside, false);
}

TEST(World3D, shade_hit2)
{
    World3D<float> world{};
    Ray3D ray{Tuple3D<float>{0, 0, 0}, Vec3D<float>{0, 0, 1}};
    Sphere3D<float> sphere = {1.0, "name"};
    Intersection3D<float> intersection(0.5, sphere);
    Comps3D<float> comps = world.prepare_computations(intersection, ray);

    Tuple3D<float> light_position{0, 0.25, 0};
    Color3D<float> light_color{1, 1, 1};

    world.light = PointLight3D<float>{light_position, light_color} ;
    Color3D<float> shade = world.shade_hit(comps);

    EXPECT_NEAR(shade.r, 0.90498, 0.001);
    EXPECT_NEAR(shade.g, 0.90498, 0.001);
    EXPECT_NEAR(shade.b, 0.90498, 0.001);

    EXPECT_EQ(comps.inside, true);
}

TEST(World3D, ColorAtNothing)
{
    World3D<float> world{};
    Ray3D ray{Tuple3D<float>{0, 0, -5}, Vec3D<float>{0, 1, 0}};
    
    Color3D<float> color = world.color_at(ray);

    EXPECT_NEAR(color.r, 0, 0.0001);
    EXPECT_NEAR(color.g, 0, 0.0001);
    EXPECT_NEAR(color.b, 0, 0.0001);
}

TEST(World3D, ColorAtSomething)
{
    World3D<float> world{};
    Ray3D ray{Tuple3D<float>{0, 0, -5}, Vec3D<float>{0, 0, 1}};

    Color3D<float> color = world.color_at(ray);

    EXPECT_NEAR(color.r, 0.38066, 0.0001);
    EXPECT_NEAR(color.g, 0.47583, 0.0001);
    EXPECT_NEAR(color.b, 0.2855, 0.0001);
}

TEST(World3D, ColorAtFromBehind)
{
    World3D<float> world{};
    Ray3D ray{Tuple3D<float>{0, 0, 0.75}, Vec3D<float>{0, 0, -1}};
    Sphere3D<float> *outer = &world.objects.at(0); //{1.0, "name"};
    outer->material.ambient = 1.f;
    Sphere3D<float> *inner = &world.objects.at(1); //{1.0, "name"};
    inner->material.ambient = 1.f;

    Color3D<float> color = world.color_at(ray);

    EXPECT_NEAR(color.r, inner->material.color.r, 0.0001);
    EXPECT_NEAR(color.g, inner->material.color.g, 0.0001);
    EXPECT_NEAR(color.b, inner->material.color.b, 0.0001);
}