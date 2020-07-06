#include <gtest/gtest.h> // googletest header file

#include <string>
#include <cmath>

#include "canvas3d.hpp"

//Vec3D
TEST(Canvas3D, Create)
{
    int width = 10;
    int height = 20;
    Ray_Tracer::Canvas3d::Canvas3d canvas {width, height};
    EXPECT_EQ(canvas.width, width);
    EXPECT_EQ(canvas.height, height);

    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            Ray_Tracer::Color3D::Color3D<float> color = canvas.colors[i][j];
            EXPECT_NEAR(color.r, 0.0, 0.001);
            EXPECT_NEAR(color.g, 0.0, 0.001);
            EXPECT_NEAR(color.b, 0.0, 0.001);
        }
    }
}

TEST(Canvas3D, WritePixels)
{
    int width = 10;
    int height = 20;

    int x = 2;
    int y = 3;

    Ray_Tracer::Color3D::Color3D<float> red{1.f, 0.f, 0.f};
    Ray_Tracer::Canvas3d::Canvas3d canvas{width, height};

    canvas.write_pixels(x, y, red);
    EXPECT_NEAR(canvas.getPixel(x, y).r, red.r, 0.0001);
    EXPECT_NEAR(canvas.getPixel(x, y).g, red.g, 0.0001);
    EXPECT_NEAR(canvas.getPixel(x, y).b, red.b, 0.0001);
}
