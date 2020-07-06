#include "gtest/gtest.h"

#include "tuple3d_test.hpp"
#include "vec3d_test.hpp"

float EPSILON = std::numeric_limits<float>::epsilon();

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
