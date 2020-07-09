#include <gtest/gtest.h> // googletest header file

#include <string>
#include <cmath>

#include "camera3d.hpp"
#include "color3d.hpp"
#include "intersection3d.hpp"
#include "intersection3d_collection.hpp"
#include "material3d.hpp"
#include "point_light3d.hpp"
#include "ray3d.hpp"
#include "sphere3d.hpp"
#include "tuple3d.hpp"
#include "util3d.hpp"
#include "vec3d.hpp"
#include "world3d.hpp"

using namespace Ray_Tracer;

TEST(Camera, DefaultCamera){
    Tuple3D<float> from{ 0, 0, 0 };
    Tuple3D<float> to{0,0,-1};
    Vec3D<float> up{0,1,0};
    //Matrix3D<float> t = Matrix3D<float>::view_transform(from, to, up);
    bool is_the_same = ( t == Matrix3D<float>::get_generic_identity_matrix());

}
