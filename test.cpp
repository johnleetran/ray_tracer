#include "gtest/gtest.h"

#include "camera3d_test.hpp"
#include "canvas3d_test.hpp"
#include "color3d_test.hpp"
#include "lights-and-shading.hpp"
#include "matrix3d_test.hpp"
#include "ray3d_test.hpp"
#include "tuple3d_test.hpp"
#include "vec3d_test.hpp"
#include "world3d_test.hpp"

float EPSILON = std::numeric_limits<float>::epsilon();

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
