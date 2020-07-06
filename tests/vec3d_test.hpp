#include <gtest/gtest.h> // googletest header file

#include <string>
#include <cmath>

#include "vec3d.hpp"

//Vec3D
TEST(Vec3D, Adding)
{
    Ray_Tracer::Vec3D::Vec3D<int> vec1{3, 2, 1};
    Ray_Tracer::Vec3D::Vec3D<int> vec2{5, 6, 7};

    Ray_Tracer::Vec3D::Vec3D<int> vec_value = vec1 + vec2;
    Ray_Tracer::Vec3D::Vec3D<int> vec_answer{8, 8, 8};

    EXPECT_EQ(vec_value.x, vec_answer.x);
    EXPECT_EQ(vec_value.y, vec_answer.y);
    EXPECT_EQ(vec_value.z, vec_answer.z);
}
TEST(Vec3D, Subtraction)
{
    Ray_Tracer::Vec3D::Vec3D<int> vec1 = {3, 2, 1};
    Ray_Tracer::Vec3D::Vec3D<int> vec2 = {5, 6, 7};

    Ray_Tracer::Vec3D::Vec3D<int> vec_value = vec1 - vec2;
    Ray_Tracer::Vec3D::Vec3D<int> vec_answer = {-2, -4, -6};

    EXPECT_EQ(vec_value.x, vec_answer.x);
    EXPECT_EQ(vec_value.y, vec_answer.y);
    EXPECT_EQ(vec_value.z, vec_answer.z);
}

TEST(Vec3D, Negation)
{
    Ray_Tracer::Vec3D::Vec3D<int> vec1 = {1, -2, 3};

    Ray_Tracer::Vec3D::Vec3D<int> vec_value = -vec1;
    Ray_Tracer::Vec3D::Vec3D<int> vec_answer = {-1, 2, -3};

    EXPECT_EQ(vec_value.x, vec_answer.x);
    EXPECT_EQ(vec_value.y, vec_answer.y);
    EXPECT_EQ(vec_value.z, vec_answer.z);
}

TEST(Vec3D, Magnitude1)
{
    Ray_Tracer::Vec3D::Vec3D<int> vec1 = {1, 0, 0};

    int vec_value = vec1.magnitude();
    int vec_answer = 1;

    EXPECT_EQ(vec_value, vec_answer);
}

TEST(Vec3D, Magnitude2)
{
    Ray_Tracer::Vec3D::Vec3D<int> vec1 = {0, 1, 0};

    int vec_value = vec1.magnitude();
    int vec_answer = 1;

    EXPECT_EQ(vec_value, vec_answer);
}

TEST(Vec3D, Magnitude3)
{
    Ray_Tracer::Vec3D::Vec3D<int> vec1 = {0, 0, 1};

    int vec_value = vec1.magnitude();
    int vec_answer = 1;

    EXPECT_EQ(vec_value, vec_answer);
}

TEST(Vec3D, Magnitude4)
{
    Ray_Tracer::Vec3D::Vec3D<float> vec1 = {1.f, 2.f, 3.f};

    float vec_value = vec1.magnitude();
    float vec_answer = std::sqrt(14);

    EXPECT_NEAR(vec_value, vec_answer, 0.0001);
}

TEST(Vec3D, Magnitude5)
{
    Ray_Tracer::Vec3D::Vec3D<float> vec1 = {-1.f, -2.f, -3.f};

    float vec_value = vec1.magnitude();
    float vec_answer = std::sqrt(14);

    EXPECT_NEAR(vec_value, vec_answer, 0.0001);
}

TEST(Vec3D, Normalize1)
{
    Ray_Tracer::Vec3D::Vec3D<float> vec1 = {1.f, 2.f, 3.f};

    Ray_Tracer::Vec3D::Vec3D<float> vec_value = vec1.normalize();
    float answer_x = 1.f / std::sqrt(14);
    float answer_y = 2.f / std::sqrt(14);
    float answer_z = 3.f / std::sqrt(14);
    Ray_Tracer::Vec3D::Vec3D<float> vec_answer = {answer_x, answer_y, answer_z};

    EXPECT_NEAR(vec_value.x, vec_answer.x, 0.001);
    EXPECT_NEAR(vec_value.y, vec_answer.y, 0.001);
    EXPECT_NEAR(vec_value.z, vec_answer.z, 0.001);
}

TEST(Vec3D, Normalize2)
{
    Ray_Tracer::Vec3D::Vec3D<float> vec1 = {1.f,2.f,3.f};

    Ray_Tracer::Vec3D::Vec3D<float> vec_value = vec1.normalize();
    float answer_x = 1.f / std::sqrt(14);
    float answer_y = 2.f / std::sqrt(14);
    float answer_z = 3.f / std::sqrt(14);
    Ray_Tracer::Vec3D::Vec3D<float> vec_answer = {answer_x, answer_y, answer_z};
    float vec_value_mag = vec_answer.magnitude();
    float vec_answer_mag = 1.0;
    EXPECT_NEAR(vec_value_mag, vec_answer_mag, 0.001);
}

TEST(Vec3D, Dot1)
{
    Ray_Tracer::Vec3D::Vec3D<float> vec1 = {1, 2, 3};
    Ray_Tracer::Vec3D::Vec3D<float> vec2 = {2, 3, 4};

    float vec_value = vec1.dot(vec2);
    float vec_answer = 20;
    EXPECT_NEAR(vec_value, vec_answer, 0.001);
}

TEST(Vec3D, Cross1)
{
    Ray_Tracer::Vec3D::Vec3D<float> vec1 = {1, 2, 3};
    Ray_Tracer::Vec3D::Vec3D<float> vec2 = {2, 3, 4};

    Ray_Tracer::Vec3D::Vec3D<float> vec_value = vec1.cross(vec2);
    Ray_Tracer::Vec3D::Vec3D<float> vec_answer = {-1, 2, -1};

    EXPECT_NEAR(vec_value.x, vec_answer.x, 0.001);
    EXPECT_NEAR(vec_value.y, vec_answer.y, 0.001);
    EXPECT_NEAR(vec_value.z, vec_answer.z, 0.001);
}

TEST(Vec3D, Cross2)
{
    Ray_Tracer::Vec3D::Vec3D<float> vec1 = {1, 2, 3};
    Ray_Tracer::Vec3D::Vec3D<float> vec2 = {2, 3, 4};

    Ray_Tracer::Vec3D::Vec3D<float> vec_value = vec2.cross(vec1);
    Ray_Tracer::Vec3D::Vec3D<float> vec_answer = {1, -2, 1};

    EXPECT_NEAR(vec_value.x, vec_answer.x, 0.001);
    EXPECT_NEAR(vec_value.y, vec_answer.y, 0.001);
    EXPECT_NEAR(vec_value.z, vec_answer.z, 0.001);
}