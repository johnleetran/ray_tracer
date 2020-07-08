#include <gtest/gtest.h> // googletest header file

#include <string>
#include <cmath>

#include "color3d.hpp"

//Vec3D
TEST(Color3D, Create){
    float r = 0.5;
    float g = 0.4;
    float b = 1.7;
    Ray_Tracer::Color3D<float> color1{r, g, b};
    EXPECT_NEAR(color1.r, r, 0.0001);
    EXPECT_NEAR(color1.g, g, 0.0001);
    EXPECT_NEAR(color1.b, b, 0.0001);
}

TEST(Color3D, Adding)
{
    Ray_Tracer::Color3D<float> color1{0.9, 0.6, 0.75};
    Ray_Tracer::Color3D<float> color2{0.7, 0.1, 0.25};

    Ray_Tracer::Color3D<float> color_vaule = color1 + color2;
    Ray_Tracer::Color3D<float> answer_color{1.6, 0.7, 1.0};

    EXPECT_NEAR(color_vaule.r, answer_color.r, 0.0001);
    EXPECT_NEAR(color_vaule.g, answer_color.g, 0.0001);
    EXPECT_NEAR(color_vaule.b, answer_color.b, 0.0001);
}

TEST(Color3D, Subtraction)
{
    Ray_Tracer::Color3D<float> color1{0.9, 0.6, 0.75};
    Ray_Tracer::Color3D<float> color2{0.7, 0.1, 0.25};

    Ray_Tracer::Color3D<float> color_vaule = color1 - color2;
    Ray_Tracer::Color3D<float> answer_color{0.2, 0.5, 0.5};

    EXPECT_NEAR(color_vaule.r, answer_color.r, 0.0001);
    EXPECT_NEAR(color_vaule.g, answer_color.g, 0.0001);
    EXPECT_NEAR(color_vaule.b, answer_color.b, 0.0001);
}

TEST(Color3D, Scale)
{
    Ray_Tracer::Color3D<float> color1{0.2, 0.3, 0.4};

    Ray_Tracer::Color3D<float> color_vaule = color1.scale(2.f);
    Ray_Tracer::Color3D<float> answer_color{0.4, 0.6, 0.8};

    EXPECT_NEAR(color_vaule.r, answer_color.r, 0.0001);
    EXPECT_NEAR(color_vaule.g, answer_color.g, 0.0001);
    EXPECT_NEAR(color_vaule.b, answer_color.b, 0.0001);
}

TEST(Color3D, Multiply)
{
    Ray_Tracer::Color3D<float> color1{1, 0.2, 0.4};
    Ray_Tracer::Color3D<float> color2{0.9, 1, 0.1};

    Ray_Tracer::Color3D<float> color_vaule = color1 * color2;
    Ray_Tracer::Color3D<float> answer_color{0.9, 0.2, 0.04};

    EXPECT_NEAR(color_vaule.r, answer_color.r, 0.0001);
    EXPECT_NEAR(color_vaule.g, answer_color.g, 0.0001);
    EXPECT_NEAR(color_vaule.b, answer_color.b, 0.0001);
}