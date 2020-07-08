#include <gtest/gtest.h> // googletest header file

#include <string>
#include "tuple3d.hpp"

TEST(Tuples, Equale)
{
    Ray_Tracer::Tuple3D<float> tuple1 = {1, 2, 3, 4};
    Ray_Tracer::Tuple3D<float> tuple2 = {1, 2, 3, 4};

    EXPECT_EQ(tuple1.x, tuple2.x);
    EXPECT_EQ(tuple1.y, tuple2.y);
    EXPECT_EQ(tuple1.z, tuple2.z);
    EXPECT_EQ(tuple1.w, tuple2.w);
}

TEST(Tuples, NotEquals)
{
    Ray_Tracer::Tuple3D<float> tuple1 = {1, 2, 3, 4};
    Ray_Tracer::Tuple3D<float> tuple2 = {1, 2, 3, 5};

    EXPECT_EQ(tuple1.x, tuple2.x);
    EXPECT_EQ(tuple1.y, tuple2.y);
    EXPECT_EQ(tuple1.z, tuple2.z);
    EXPECT_NE(tuple1.w, tuple2.w);
}

TEST(Tuples, Adding)
{
    Ray_Tracer::Tuple3D<float> tuple1{3, -2, 5, 1};
    Ray_Tracer::Tuple3D<float> tuple2{-2, 3, 1, 0};

    Ray_Tracer::Tuple3D<float> tup_value = tuple1 + tuple2;
    Ray_Tracer::Tuple3D<float> tuple_answer{1, 1, 6, 1};

    EXPECT_EQ(tup_value.x, tuple_answer.x);
    EXPECT_EQ(tup_value.y, tuple_answer.y);
    EXPECT_EQ(tup_value.z, tuple_answer.z);
    EXPECT_EQ(tup_value.w, tuple_answer.w);
}

TEST(Tuples, Subtraction)
{
    Ray_Tracer::Tuple3D<float> tuple1 = {3, -2, 5, 1};
    Ray_Tracer::Tuple3D<float> tuple2 = {-2, 3, 1, 0};

    Ray_Tracer::Tuple3D<float> tup_value = tuple1 - tuple2;
    Ray_Tracer::Tuple3D<float> tup_answer = {5, -5, 4, 1};

    EXPECT_EQ(tup_value.x, tup_answer.x);
    EXPECT_EQ(tup_value.y, tup_answer.y);
    EXPECT_EQ(tup_value.z, tup_answer.z);
    EXPECT_EQ(tup_value.w, tup_answer.w);
}

TEST(Tuple, Negation)
{
    Ray_Tracer::Tuple3D<float> tup = {1, -2, 3, -4};

    Ray_Tracer::Tuple3D<float> tup_value = -tup;
    Ray_Tracer::Tuple3D<float> tup_answer = {-1, 2, -3, 4};

    EXPECT_NEAR(tup_value.x, tup_answer.x, 0.001);
    EXPECT_NEAR(tup_value.y, tup_answer.y, 0.001);
    EXPECT_NEAR(tup_value.z, tup_answer.z, 0.001);
    EXPECT_NEAR(tup_value.w, tup_answer.w, 0.001);
}

TEST(Tuple3D, Multiply1)
{
    Ray_Tracer::Tuple3D<float> tup = {1.f, -2.f, 3.f, -4.f};
    float multiplier = 3.5f;

    Ray_Tracer::Tuple3D<float> tup_value = tup * multiplier;
    Ray_Tracer::Tuple3D<float> tup_answer = {3.5, -7, 10.5, -14};

    EXPECT_NEAR(tup_value.x, tup_answer.x, 0.001);
    EXPECT_NEAR(tup_value.y, tup_answer.y, 0.001);
    EXPECT_NEAR(tup_value.z, tup_answer.z, 0.001);
    EXPECT_NEAR(tup_value.w, tup_answer.w, 0.001);
}

TEST(Tuple3D, Multiply2)
{
    Ray_Tracer::Tuple3D<float> tup = {1.f, -2.f, 3.f, -4.f};
    float multiplier = 0.5f;

    Ray_Tracer::Tuple3D<float> tup_value = tup * multiplier;
    Ray_Tracer::Tuple3D<float> tup_answer = {0.5, -1, 1.5, -2};

    EXPECT_NEAR(tup_value.x, tup_answer.x, 0.001);
    EXPECT_NEAR(tup_value.y, tup_answer.y, 0.001);
    EXPECT_NEAR(tup_value.z, tup_answer.z, 0.001);
    EXPECT_NEAR(tup_value.w, tup_answer.w, 0.001);
}

TEST(Tuple3D, Normalize1)
{
    Ray_Tracer::Tuple3D<float> tup1 = {1.f, 2.f, 3.f, 4.f};

    Ray_Tracer::Tuple3D<float> tup_value = tup1.normalize();
    float answer_x = 1.f / std::sqrt(30);
    float answer_y = 2.f / std::sqrt(30);
    float answer_z = 3.f / std::sqrt(30);
    float answer_w = 4.f / std::sqrt(30);

    Ray_Tracer::Tuple3D<float> tup_answer = {answer_x, answer_y, answer_z, answer_w};

    EXPECT_NEAR(tup_value.x, tup_answer.x, 0.001);
    EXPECT_NEAR(tup_value.y, tup_answer.y, 0.001);
    EXPECT_NEAR(tup_value.z, tup_answer.z, 0.001);
    EXPECT_NEAR(tup_value.w, tup_answer.w, 0.001);
}

TEST(Tuple3D, Normalize2)
{
    Ray_Tracer::Tuple3D<float> tup1 = {1.f, 2.f, 3.f, 4.f};

    Ray_Tracer::Tuple3D<float> tup_value = tup1.normalize();
    float answer_x = 1.f / std::sqrt(30);
    float answer_y = 2.f / std::sqrt(30);
    float answer_z = 3.f / std::sqrt(30);
    float answer_w = 4.f / std::sqrt(30);

    Ray_Tracer::Tuple3D<float> tup_answer = {answer_x, answer_y, answer_z, answer_w};
    float tup_value_mag = tup_answer.magnitude();
    float tup_answer_mag = 1.0;
    EXPECT_NEAR(tup_value_mag, tup_answer_mag, 0.001);
}