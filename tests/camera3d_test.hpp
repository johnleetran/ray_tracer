#include <gtest/gtest.h> // googletest header file

#include <string>
#include <cmath>

#include "camera3d.hpp"
#include "canvas3d.hpp"
#include "color3d.hpp"
#include "intersection3d.hpp"
#include "intersection3d_collection.hpp"
#include "material3d.hpp"
#include "point_light3d.hpp"
#include "ray_for_pixel3d.hpp"
#include "ray3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"
#include "util3d.hpp"
#include "vec3d.hpp"
#include "world3d.hpp"

using namespace Ray_Tracer;

TEST(Camera, DefaultViewTransform){
    Tuple3D<float> from{ 0, 0, 0 };
    Tuple3D<float> to{0,0,-1};
    Vec3D<float> up{0,1,0};
    Matrix3D<float> t = Camera3D<float>::view_transform(from, to, up);
    bool is_the_same = ( t == Matrix3D<float>::get_generic_identity_matrix());
    EXPECT_EQ(is_the_same, true);
}

TEST(Camera, PositiveZDirection)
{
    Tuple3D<float> from{0, 0, 0};
    Tuple3D<float> to{0, 0, 1};
    Vec3D<float> up{0, 1, 0};
    Matrix3D<float> t = Camera3D<float>::view_transform(from, to, up);
    Matrix3D<float> scaling = t.scaling(-1, 1, -1);
    bool is_the_same = (t == scaling);
    EXPECT_EQ(is_the_same, true);
}

TEST(Camera, MoveTheWorld)
{
    Tuple3D<float> from{0, 0, 8};
    Tuple3D<float> to{0, 0, 0};
    Vec3D<float> up{0, 1, 0};
    Matrix3D<float> t = Camera3D<float>::view_transform(from, to, up);
    Matrix3D<float> translation = t.translate(0, 0, -8);
    bool is_the_same = (t == translation);
    EXPECT_EQ(is_the_same, true);
}

TEST(Camera, CreateCamera)
{
    float hsize = 160;
    float vsize = 120;
    float field_of_view = 3.14/2;
    Camera3D<float> camera{hsize, vsize, field_of_view};
    EXPECT_NEAR(camera.hsize, hsize, 0.0001);
    EXPECT_NEAR(camera.vsize, vsize, 0.0001);
    EXPECT_NEAR(camera.field_of_view, field_of_view, 0.0001);

    bool is_the_same = (camera.transform() == Matrix3D<float>::get_generic_identity_matrix());
    EXPECT_EQ(is_the_same, true);
}

TEST(Camera, PixelSize1)
{
    float hsize = 200;
    float vsize = 125;
    float field_of_view = 3.14 / 2;
    Camera3D<float> camera{hsize, vsize, field_of_view};
    EXPECT_NEAR(camera.pixel_size, 0.01, 0.0001);
}

TEST(Camera, PixelSize2)
{
    float hsize = 125;
    float vsize = 200;
    float field_of_view = 3.14 / 2;
    Camera3D<float> camera{hsize, vsize, field_of_view};
    EXPECT_NEAR(camera.pixel_size, 0.01, 0.0001);
}

TEST(Camera, RayForPixel1)
{
    float hsize = 201;
    float vsize = 101;
    float field_of_view = 3.14 / 2;
    Camera3D<float> camera{hsize, vsize, field_of_view};
    Ray3D<float> ray = RayForPixel3D<float>::ray_for_pixel(camera, 100, 50);
    EXPECT_NEAR(ray.origin.x, 0, 0.001);
    EXPECT_NEAR(ray.origin.y, 0, 0.001);
    EXPECT_NEAR(ray.origin.z, 0, 0.001);

    EXPECT_NEAR(ray.direction.x, 0, 0.001);
    EXPECT_NEAR(ray.direction.y, 0, 0.001);
    EXPECT_NEAR(ray.direction.z, -1, 0.001);
}

TEST(Camera, RayForPixel2)
{
    float hsize = 201;
    float vsize = 101;
    float field_of_view = 3.14 / 2;
    Camera3D<float> camera{hsize, vsize, field_of_view};
    Ray3D<float> ray = RayForPixel3D<float>::ray_for_pixel(camera, 0, 0);
    EXPECT_NEAR(ray.origin.x, 0, 0.001);
    EXPECT_NEAR(ray.origin.y, 0, 0.001);
    EXPECT_NEAR(ray.origin.z, 0, 0.001);

    EXPECT_NEAR(ray.direction.x, 0.66519, 0.001);
    EXPECT_NEAR(ray.direction.y, 0.33259, 0.001);
    EXPECT_NEAR(ray.direction.z, -0.66851, 0.001);
}

TEST(Camera, RayForPixel3)
{
    float non_axis = std::sqrt(2) / 2.f;
    float hsize = 201;
    float vsize = 101;
    float field_of_view = 3.14 / 2;
    Camera3D<float> camera{hsize, vsize, field_of_view};
    camera.transform_matrix = camera.transform_matrix.rotation_y(3.14 / 4.f) * camera.transform_matrix.translate(0, -2, 5);

    Ray3D<float> ray = RayForPixel3D<float>::ray_for_pixel(camera, 100, 50);
    EXPECT_NEAR(ray.origin.x, 0, 0.001);
    EXPECT_NEAR(ray.origin.y, 2, 0.001);
    EXPECT_NEAR(ray.origin.z, -5, 0.001);

    EXPECT_NEAR(ray.direction.x, non_axis, 0.001);
    EXPECT_NEAR(ray.direction.y, 0, 0.001);
    EXPECT_NEAR(ray.direction.z, -non_axis, 0.001);
}

TEST(Camera, RenderMiddle)
{
    World3D<float> w{};
    Camera3D<float> c(11,11, 3.14/2.f);
    Tuple3D<float> from{0,0,-5};
    Tuple3D<float> to{0,0,0};
    Vec3D<float> up{0,1,0};
    Canvas3D<float> canvas{11, 11};
    c.transform_matrix = Camera3D<float>::view_transform(from, to, up);
    canvas.render(c, w);
    float r = canvas.getPixel(5, 5).r;
    float g = canvas.getPixel(5, 5).g;
    float b = canvas.getPixel(5, 5).b;

    EXPECT_NEAR(r, 0.38066, 0.001);
    EXPECT_NEAR(g, 0.47583, 0.001);
    EXPECT_NEAR(b, 0.2855, 0.001);
}
