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

    std::optional<std::vector<float>> intersection_points = Ray_Tracer::Intersection3D<float>::intersect(ray, sphere);
    EXPECT_NEAR(intersection_points->at(0), 4.0, 0.0001);
    EXPECT_NEAR(intersection_points->at(1), 6.0, 0.0001);
    EXPECT_GT(sphere.id.length(), 0);
}

TEST(Ray3D, SphereIntersect2)
{
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{0, 1, -5};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 0, 1};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    std::string uuid = Ray_Tracer::get_uuid();

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, uuid};

    std::optional<std::vector<float>> intersection_points = Ray_Tracer::Intersection3D<float>::intersect(ray, sphere);
    EXPECT_NEAR(intersection_points->at(0), 5.0, 0.0001);
    EXPECT_NEAR(intersection_points->at(1), 5.0, 0.0001);
    EXPECT_GT(sphere.id.length(), 0);
}

TEST(Ray3D, SphereIntersect3)
{
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{0, 2, -5};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 0, 1};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    std::string uuid = Ray_Tracer::get_uuid();

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, uuid};

    std::optional<std::vector<float>> intersection_points = Ray_Tracer::Intersection3D<float>::intersect(ray, sphere);
    EXPECT_EQ(intersection_points, std::nullopt);
    EXPECT_GT(sphere.id.length(), 0);
}

TEST(Ray3D, SphereIntersect4)
{
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{0, 0, 0};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 0, 1};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    std::string uuid = Ray_Tracer::get_uuid();

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, uuid};

    std::optional<std::vector<float>> intersection_points = Ray_Tracer::Intersection3D<float>::intersect(ray, sphere);
    EXPECT_NEAR(intersection_points->at(0), -1.0, 0.0001);
    EXPECT_NEAR(intersection_points->at(1),  1.0, 0.0001);
    EXPECT_GT(sphere.id.length(), 0);
}

TEST(Ray3D, SphereIntersect5)
{
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{0, 0, 5};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 0, 1};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    std::string uuid = Ray_Tracer::get_uuid();

    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, uuid};

    std::optional<std::vector<float>> intersection_points = Ray_Tracer::Intersection3D<float>::intersect(ray, sphere);
    EXPECT_NEAR(intersection_points->at(0), -6.0, 0.0001);
    EXPECT_NEAR(intersection_points->at(1), -4.0, 0.0001);
    EXPECT_GT(sphere.id.length(), 0);
}

TEST(Ray3D, IntersectObject1)
{
    std::string uuid = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere{1.0, uuid};

    Ray_Tracer::Intersection3D<float> intersection{3.5f, sphere};
    EXPECT_NEAR(intersection.t, 3.5, 0.0001);
    EXPECT_EQ(intersection.object.id, uuid);
}

TEST(Ray3D, IntersectCollection1)
{
    std::string uuid1 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere1{1.0, uuid1};
    Ray_Tracer::Intersection3D<float> intersection1{3.5f, sphere1};

    std::string uuid2 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere2{1.0, uuid2};
    Ray_Tracer::Intersection3D<float> intersection2{13.5f, sphere2};

    Ray_Tracer::Intersection3D_Collection<float> intersection_collection{};
    intersection_collection.add(intersection1);
    intersection_collection.add(intersection2);

    EXPECT_NEAR(intersection_collection.get(0).t, 3.5, 0.0001);
    EXPECT_EQ(intersection_collection.get(0).object.id, sphere1.id);

    EXPECT_NEAR(intersection_collection.get(1).t, 13.5, 0.0001);
    EXPECT_EQ(intersection_collection.get(1).object.id, sphere2.id);
}

TEST(Ray3D, IntersectCollectionHit1)
{
    std::string uuid1 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere1{1.0, uuid1};
    Ray_Tracer::Intersection3D<float> intersection1{3.5f, sphere1};

    std::string uuid2 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere2{1.0, uuid2};
    Ray_Tracer::Intersection3D<float> intersection2{13.5f, sphere2};

    Ray_Tracer::Intersection3D_Collection<float> intersection_collection{};
    intersection_collection.add(intersection2);
    intersection_collection.add(intersection1);
    std::optional<Ray_Tracer::Intersection3D<float>> hit = intersection_collection.get_hit();

    EXPECT_EQ(hit->object.id, intersection1.object.id);
}

TEST(Ray3D, IntersectCollectionHit2)
{
    std::string uuid1 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere1{1.0, uuid1};
    Ray_Tracer::Intersection3D<float> intersection1{-1.f, sphere1};

    std::string uuid2 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere2{1.0, uuid2};
    Ray_Tracer::Intersection3D<float> intersection2{1.f, sphere2};

    Ray_Tracer::Intersection3D_Collection<float> intersection_collection{};
    intersection_collection.add(intersection2);
    intersection_collection.add(intersection1);

    std::optional<Ray_Tracer::Intersection3D<float>> hit = intersection_collection.get_hit();
    EXPECT_EQ(hit->object.id, intersection2.object.id);
}

TEST(Ray3D, IntersectCollectionHit3)
{
    std::string uuid1 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere1{1.0, uuid1};
    Ray_Tracer::Intersection3D<float> intersection1{-2.f, sphere1};

    std::string uuid2 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere2{1.0, uuid2};
    Ray_Tracer::Intersection3D<float> intersection2{-1.f, sphere2};

    Ray_Tracer::Intersection3D_Collection<float> intersection_collection{};
    intersection_collection.add(intersection2);
    intersection_collection.add(intersection1);

    std::optional<Ray_Tracer::Intersection3D<float>> hit = intersection_collection.get_hit();

    EXPECT_EQ(hit, std::nullopt);
}

TEST(Ray3D, IntersectCollectionHit4)
{
    std::string uuid1 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere1{1.0, uuid1};
    Ray_Tracer::Intersection3D<float> intersection1{5.f, sphere1};

    std::string uuid2 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere2{1.0, uuid2};
    Ray_Tracer::Intersection3D<float> intersection2{7.f, sphere2};

    std::string uuid3 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere3{1.0, uuid3};
    Ray_Tracer::Intersection3D<float> intersection3{-3.f, sphere3};

    std::string uuid4 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere4{1.0, uuid4};
    Ray_Tracer::Intersection3D<float> intersection4{2.f, sphere4};

    Ray_Tracer::Intersection3D_Collection<float> intersection_collection{};
    intersection_collection.add(intersection1);
    intersection_collection.add(intersection2);
    intersection_collection.add(intersection3);
    intersection_collection.add(intersection4);

    std::optional<Ray_Tracer::Intersection3D<float>> hit = intersection_collection.get_hit();

    EXPECT_EQ(hit->t, 2);
}

TEST(Ray3D, RayTranslation){
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{1, 2, 3};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 1, 0};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    Ray_Tracer::Matrix3D::Matrix3D<float> mat{};
    Ray_Tracer::Matrix3D::Matrix3D<float> translate_matrix = mat.translate(3, 4, 5);
    Ray_Tracer::Ray3D::Ray3D<float> transformed_ray = ray.transform(translate_matrix);

    EXPECT_NEAR(transformed_ray.origin.x, 4, 0.0001);
    EXPECT_NEAR(transformed_ray.origin.y, 6, 0.0001);
    EXPECT_NEAR(transformed_ray.origin.z, 8, 0.0001);

    EXPECT_NEAR(transformed_ray.direction.x, 0, 0.0001);
    EXPECT_NEAR(transformed_ray.direction.y, 1, 0.0001);
    EXPECT_NEAR(transformed_ray.direction.z, 0, 0.0001);
}

TEST(Ray3D, RayScaling)
{
    Ray_Tracer::Tuple3D::Tuple3D<float> origin{1, 2, 3};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 1, 0};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    Ray_Tracer::Matrix3D::Matrix3D<float> mat{};
    Ray_Tracer::Matrix3D::Matrix3D<float> translate_matrix = mat.scaling(2, 3, 4);
    Ray_Tracer::Ray3D::Ray3D<float> transformed_ray = ray.transform(translate_matrix);

    EXPECT_NEAR(transformed_ray.origin.x, 2, 0.0001);
    EXPECT_NEAR(transformed_ray.origin.y, 6, 0.0001);
    EXPECT_NEAR(transformed_ray.origin.z, 12, 0.0001);

    EXPECT_NEAR(transformed_ray.direction.x, 0, 0.0001);
    EXPECT_NEAR(transformed_ray.direction.y, 3, 0.0001);
    EXPECT_NEAR(transformed_ray.direction.z, 0, 0.0001);
}

TEST(Ray3D, SphereTransform1)
{
    std::string uuid1 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere1{1.0, uuid1};
    Ray_Tracer::Matrix3D::Matrix3D<float> real_identity_matrix = Ray_Tracer::Matrix3D::Matrix3D<float>::get_generic_identity_matrix();
    Ray_Tracer::Matrix3D::Matrix3D<float> identity_matrix_from_sphere = sphere1.get_transform();

    bool is_the_same = (identity_matrix_from_sphere == real_identity_matrix);
    EXPECT_EQ(is_the_same, true);
}

TEST(Ray3D, SphereTransform2)
{
    std::string uuid1 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere1{1.0, uuid1};
    Ray_Tracer::Matrix3D::Matrix3D<float> &transform_matrix = sphere1.transform_matrix;
    Ray_Tracer::Matrix3D::Matrix3D<float> translate_matrix = transform_matrix.translate(2, 3, 4);
    sphere1.transform(translate_matrix);

    bool is_same = (transform_matrix == translate_matrix);
    EXPECT_EQ(is_same, true);
}

TEST(Ray3D, RaySphereIntersection1)
{

    Ray_Tracer::Tuple3D::Tuple3D<float> origin{0, 0, -5};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 0, 1};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    std::string uuid1 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere1{1.0, uuid1};

    Ray_Tracer::Matrix3D::Matrix3D<float> &transform_matrix = sphere1.transform_matrix;
    Ray_Tracer::Matrix3D::Matrix3D<float> scaling_matrix = transform_matrix.scaling(2, 2, 2);
    sphere1.transform(scaling_matrix);

    std::optional<std::vector<float>> intersection_points = Ray_Tracer::Intersection3D<float>::intersect(ray, sphere1);
    EXPECT_NEAR(intersection_points->at(0), 3, 0.0001);
    EXPECT_NEAR(intersection_points->at(1), 7, 0.0001);
}

TEST(Ray3D, RaySphereIntersection2)
{

    Ray_Tracer::Tuple3D::Tuple3D<float> origin{0, 0, -5};
    Ray_Tracer::Vec3D::Vec3D<float> direction{0, 0, 1};
    Ray_Tracer::Ray3D::Ray3D<float> ray{origin, direction};

    std::string uuid1 = Ray_Tracer::get_uuid();
    Ray_Tracer::Sphere3D::Sphere3D<float> sphere1{1.0, uuid1};

    Ray_Tracer::Matrix3D::Matrix3D<float> &transform_matrix = sphere1.transform_matrix;
    Ray_Tracer::Matrix3D::Matrix3D<float> translate_matrix = transform_matrix.translate(5, 0, 0);
    sphere1.transform(translate_matrix);

    std::optional<std::vector<float>> intersection_points = Ray_Tracer::Intersection3D<float>::intersect(ray, sphere1);
    EXPECT_EQ(intersection_points, std::nullopt);
}