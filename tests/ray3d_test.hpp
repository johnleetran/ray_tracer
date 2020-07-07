#include <gtest/gtest.h> // googletest header file

#include <string>
#include <cmath>

#include "ray3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"
#include "util3d.hpp"
#include "vec3d.hpp"

TEST(Ray3D, Create)
{
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{1,2,3};
    Ray_Tracer::Vec3D::Vec3D<float> direction{4, 5, 6};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};
    EXPECT_NEAR(origin.x, ray.origin.x, 0.0001);
    EXPECT_NEAR(origin.y, ray.origin.y, 0.0001);
    EXPECT_NEAR(origin.z, ray.origin.z, 0.0001);

    EXPECT_NEAR(direction.x, ray.direction.x, 0.0001);
    EXPECT_NEAR(direction.y, ray.direction.y, 0.0001);
    EXPECT_NEAR(direction.z, ray.direction.z, 0.0001);
}

TEST(Ray3D, Position)
{
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{2, 3, 4};
    Ray_Tracer::Vec3D::Vec3D<float> direction{1, 0, 0};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    Ray_Tracer::Tuple3D::Tuple3D<float> answer1{2, 3, 4};
    Ray_Tracer::Tuple3D::Tuple3D<float> position1 = ray.position(0);

    EXPECT_NEAR(position1.x, answer1.x, 0.0001);
    EXPECT_NEAR(position1.y, answer1.y, 0.0001);
    EXPECT_NEAR(position1.z, answer1.z, 0.0001);

    Ray_Tracer::Tuple3D::Tuple3D<float> answer2 {3, 3, 4};
    Ray_Tracer::Tuple3D::Tuple3D<float> position2 = ray.position(1);

    EXPECT_NEAR(position2.x, answer2.x, 0.0001);
    EXPECT_NEAR(position2.y, answer2.y, 0.0001);
    EXPECT_NEAR(position2.z, answer2.z, 0.0001);

    Ray_Tracer::Tuple3D::Tuple3D<float> answer3 {1, 3, 4};
    Ray_Tracer::Tuple3D::Tuple3D<float> position3 = ray.position(-1);

    EXPECT_NEAR(position3.x, answer3.x, 0.0001);
    EXPECT_NEAR(position3.y, answer3.y, 0.0001);
    EXPECT_NEAR(position3.z, answer3.z, 0.0001);

    Ray_Tracer::Tuple3D::Tuple3D<float> answer4{4.5, 3, 4};
    Ray_Tracer::Tuple3D::Tuple3D<float> position4 = ray.position(2.5);

    EXPECT_NEAR(position4.x, answer4.x, 0.0001);
    EXPECT_NEAR(position4.y, answer4.y, 0.0001);
    EXPECT_NEAR(position4.z, answer4.z, 0.0001);
}

TEST(Ray3D, SphereIntersect1){
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{0, 0, -5};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 0, 1};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    std::string uuid = Ray_Tracer::get_uuid();

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, uuid};

    std::vector<float> intersection_points = ray.intersect(sphere);
    EXPECT_NEAR(intersection_points[0], 4.0, 0.0001);
    EXPECT_NEAR(intersection_points[1], 6.0, 0.0001);
    EXPECT_GT(sphere.id.length(), 0);
}

TEST(Ray3D, SphereIntersect2)
{
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{0, 1, -5};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 0, 1};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    std::string uuid = Ray_Tracer::get_uuid();

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, uuid};

    std::vector<float> intersection_points = ray.intersect(sphere);
    EXPECT_NEAR(intersection_points[0], 5.0, 0.0001);
    EXPECT_NEAR(intersection_points[1], 5.0, 0.0001);
    EXPECT_GT(sphere.id.length(), 0);
}

TEST(Ray3D, SphereIntersect3)
{
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{0, 2, -5};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 0, 1};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    std::string uuid = Ray_Tracer::get_uuid();

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, uuid};

    std::vector<float> intersection_points = ray.intersect(sphere);
    EXPECT_EQ(intersection_points.size(), 0);
    EXPECT_GT(sphere.id.length(), 0);
}

TEST(Ray3D, SphereIntersect4)
{
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{0, 0, 0};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 0, 1};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    std::string uuid = Ray_Tracer::get_uuid();

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, uuid};

    std::vector<float> intersection_points = ray.intersect(sphere);
    EXPECT_NEAR(intersection_points[0], -1.0, 0.0001);
    EXPECT_NEAR(intersection_points[1],  1.0, 0.0001);
    EXPECT_GT(sphere.id.length(), 0);
}

TEST(Ray3D, SphereIntersect5)
{
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{0, 0, 5};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 0, 1};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    std::string uuid = Ray_Tracer::get_uuid();

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, uuid};

    std::vector<float> intersection_points = ray.intersect(sphere);
    EXPECT_NEAR(intersection_points[0], -6.0, 0.0001);
    EXPECT_NEAR(intersection_points[1], -4.0, 0.0001);
    EXPECT_GT(sphere.id.length(), 0);
}