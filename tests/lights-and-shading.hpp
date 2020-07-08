#include <gtest/gtest.h> // googletest header file

#include <string>
#include <cmath>

#include "intersection3d.hpp"
#include "intersection3d_collection.hpp"
#include "ray3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"
#include "util3d.hpp"
#include "vec3d.hpp"

TEST(LightsAndShading, ComputeSphereNormalsX){
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Tuple3D::Tuple3D<float> point{1,0,0};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);
    Ray_Tracer::Vec3D::Vec3D<float> answer{1, 0, 0};
    EXPECT_NEAR(n.x, answer.x, 0.001);
    EXPECT_NEAR(n.y, answer.y, 0.001);
    EXPECT_NEAR(n.z, answer.z, 0.001);
}

TEST(LightsAndShading, ComputeSphereNormalsY)
{
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Tuple3D::Tuple3D<float> point{0, 1, 0};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);
    Ray_Tracer::Vec3D::Vec3D<float> answer{0, 1, 0};
    EXPECT_NEAR(n.x, answer.x, 0.001);
    EXPECT_NEAR(n.y, answer.y, 0.001);
    EXPECT_NEAR(n.z, answer.z, 0.001);
}

TEST(LightsAndShading, ComputeSphereNormalsZ)
{
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Tuple3D::Tuple3D<float> point{0, 0, 1};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);
    Ray_Tracer::Vec3D::Vec3D<float> answer{0, 0, 1};
    EXPECT_NEAR(n.x, answer.x, 0.001);
    EXPECT_NEAR(n.y, answer.y, 0.001);
    EXPECT_NEAR(n.z, answer.z, 0.001);
}

TEST(LightsAndShading, ComputeSphereNormalsNonAxis)
{
    float non_axis = std::sqrt(3) / 3;

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Tuple3D::Tuple3D<float> point{non_axis, non_axis, non_axis};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);
    Ray_Tracer::Vec3D::Vec3D<float> answer{non_axis, non_axis, non_axis};
    EXPECT_NEAR(n.x, answer.x, 0.001);
    EXPECT_NEAR(n.y, answer.y, 0.001);
    EXPECT_NEAR(n.z, answer.z, 0.001);
}

TEST(LightsAndShading, NormalIsANormlizedVector)
{
    float non_axis = std::sqrt(3) / 3;

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Tuple3D::Tuple3D<float> point{non_axis, non_axis, non_axis};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);
    Ray_Tracer::Vec3D::Vec3D<float> nn = n.normalize();

    EXPECT_NEAR(n.x, nn.x, 0.001);
    EXPECT_NEAR(n.y, nn.y, 0.001);
    EXPECT_NEAR(n.z, nn.z, 0.001);
}

TEST(LightsAndShading, NormalTranslatedSphere)
{
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Matrix3D::Matrix3D<float> transform_matrix = sphere.get_transform();
    transform_matrix = transform_matrix.translate(0, 1, 0);
    sphere.transform(transform_matrix);
    Ray_Tracer::Tuple3D::Tuple3D<float> point{0, 1.70711, -0.70711};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);

    EXPECT_NEAR(n.x, 0, 0.001);
    EXPECT_NEAR(n.y, 0.70711, 0.001);
    EXPECT_NEAR(n.z, -0.70711, 0.001);
}

TEST(LightsAndShading, NormalScaledAndRotatedSphere)
{

    float non_axis = std::sqrt(2) / 2;

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, "sphere"};
    Ray_Tracer::Matrix3D::Matrix3D<float> transform_matrix = sphere.get_transform();
    transform_matrix = transform_matrix.scaling(1, 0.5, 1) * transform_matrix.rotation_z(3.14/5);
    sphere.transform(transform_matrix);
    Ray_Tracer::Tuple3D::Tuple3D<float> point{0, non_axis, -non_axis};
    Ray_Tracer::Vec3D::Vec3D<float> n = sphere.normalize_at(point);

    EXPECT_NEAR(n.x, 0, 0.001);
    EXPECT_NEAR(n.y, 0.97014, 0.001);
    EXPECT_NEAR(n.z, -0.24254, 0.001);
}

TEST(LightsAndShading, Reflection45Degrees)
{
    Ray_Tracer::Vec3D::Vec3D<float> v{1, -1, 0};
    Ray_Tracer::Vec3D::Vec3D<float> n{0,1,0};
    Ray_Tracer::Vec3D::Vec3D<float> r = Ray_Tracer::Vec3D::Vec3D<float>::reflect(v, n);

    EXPECT_NEAR(r.x, 1, 0.001);
    EXPECT_NEAR(r.y, 1, 0.001);
    EXPECT_NEAR(r.z, 0, 0.001);
}

TEST(LightsAndShading, ReflectionSlantedSurface)
{
    float non_axis = std::sqrt(2) / 2;

    Ray_Tracer::Vec3D::Vec3D<float> v{0, -1, 0};
    Ray_Tracer::Vec3D::Vec3D<float> n{non_axis, non_axis, 0};
    Ray_Tracer::Vec3D::Vec3D<float> r = Ray_Tracer::Vec3D::Vec3D<float>::reflect(v, n);

    EXPECT_NEAR(r.x, 1, 0.001);
    EXPECT_NEAR(r.y, 0, 0.001);
    EXPECT_NEAR(r.z, 0, 0.001);
}