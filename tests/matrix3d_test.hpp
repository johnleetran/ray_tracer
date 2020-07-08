#include <gtest/gtest.h> // googletest header file

#include <string>
#include <cmath>
#include <vector>

#include "matrix3d.hpp"

const float pi = 3.14;

TEST(Matrix3D, Create2x2)
{
    std::vector<std::vector<float>> mat{
        {-3, 5},
        {1, -2}};
    Ray_Tracer::Matrix3D<float> matrix{mat};
    for (int i; i < matrix.row; i++)
    {
        for (int j = 0; j < matrix.col; j++)
        {
            EXPECT_NEAR(matrix.matrix[i][j], mat[i][j], 0.001);
        }
    }
}

TEST(Matrix3D, Create3x3)
{
    std::vector<std::vector<float>> mat{
        {-3, 5, 0},
        {1, -2, -7},
        {0,  1 , 1}
    };
    Ray_Tracer::Matrix3D<float> matrix{mat};
    for (int i; i < matrix.row; i++)
    {
        for (int j = 0; j < matrix.col; j++)
        {
            EXPECT_NEAR(matrix.matrix[i][j], mat[i][j], 0.001);
        }
    }
}

TEST(Matrix3D, Create4x4)
{
    std::vector< std::vector<float> > mat{
        {  1,   2,   3,   4},
        {5.5, 6.5, 7.5, 8.5},
        {  9,  10,  11,  12},
        {13.5,14.5,15.5,16.5}
    };
    Ray_Tracer::Matrix3D<float> matrix{mat};
    for (int i; i < matrix.row; i++){
        for (int j = 0; j < matrix.col; j++)
        {
            EXPECT_NEAR(matrix.matrix[i][j], mat[i][j], 0.001);
        }
    }
}

TEST(Matrix3D, Equality1)
{
    std::vector<std::vector<float>> mat1{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}};
    std::vector<std::vector<float>> mat2{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}};
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> matrix2{mat2};
    bool result = (mat1 == mat2);
    EXPECT_EQ(result, true);
}

TEST(Matrix3D, Equality2)
{
    std::vector<std::vector<float>> mat1{
        {.1, .2, .3, .4},
        {.5, .6, .7, .8},
        {.9, .8, .7, .6},
        {.5, .4, .3, .2}};
    std::vector<std::vector<float>> mat2{
        {.1, .2, .3, .4},
        {.5, .6, .7, .8},
        {.9, .8, .7, .6},
        {.5, .4, .30000001, .199999999}};
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> matrix2{mat2};
    bool result = (mat1 == mat2);
    EXPECT_EQ(result, true);
}

TEST(Matrix3D, Notquality1)
{
    std::vector<std::vector<float>> mat1{
        {.1, .2, .3, .4},
        {.5, .6, .7, .8},
        {.9, .8, .7, .6},
        {.5, .4, .3, .2}};
    std::vector<std::vector<float>> mat2{
        {.1, .2, .3, .4},
        {.5, .6, .7, .8},
        {.9, .8, .7, .6},
        {.5, .4, .3001, .199999}};
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> matrix2{mat2};
    bool result = (mat1 == mat2);
    EXPECT_EQ(result, false);
}

TEST(Matrix3D, Multply1)
{
    std::vector<std::vector<float>> mat1{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    };
    std::vector<std::vector<float>> mat2{
        {-2, 1,  2,  3},
        {3,  2,  1, -1},
        {4,  3,  6,  5},
        {1,  2,  7,  8}
    };

    std::vector<std::vector<float>> answer{
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42}};

    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> matrix2{mat2};

    Ray_Tracer::Matrix3D<float> result = matrix1 * matrix2;
    Ray_Tracer::Matrix3D<float> answer_matrix{answer};

    bool eq = (result == answer_matrix);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, MultplyTuple)
{
    std::vector<std::vector<float>> mat1{
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1}};
    Ray_Tracer::Tuple3D<float> tup{1, 2, 3, 1};

    Ray_Tracer::Tuple3D<float> answer{18, 24, 33, 1};

    Ray_Tracer::Matrix3D<float> matrix1{mat1};

    Ray_Tracer::Tuple3D<float> result = matrix1 * tup;

    EXPECT_NEAR(result.x, answer.x, 0.0001);
    EXPECT_NEAR(result.y, answer.y, 0.0001);
    EXPECT_NEAR(result.z, answer.z, 0.0001);
    EXPECT_NEAR(result.w, answer.w, 0.0001);
}

TEST(Matrix3D, IdentifyMatrix)
{
    std::vector<std::vector<float>> mat1{
        {0, 1, 2, 3},
        {1, 2, 4, 8},
        {2, 4, 8, 8},
        {4, 8, 16, 32}};
    std::vector<std::vector<float>> mat2{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};

    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> matrix2{mat2};

    Ray_Tracer::Matrix3D<float> result = matrix1 * matrix2;

    bool eq = (result == matrix1);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, Transpose)
{
    std::vector<std::vector<float>> mat1{
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8}};
    std::vector<std::vector<float>> answer{
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8}};

    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> answer_matrix{answer};

    matrix1 = matrix1.transpose();

    bool eq = (answer_matrix == matrix1);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, TransposeIdentity)
{
    std::vector<std::vector<float>> mat1{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};
    std::vector<std::vector<float>> answer{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};

    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> answer_matrix{answer};

    matrix1 = matrix1.transpose();

    bool eq = (answer_matrix == matrix1);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, CalculateDeterminant2x2)
{
    std::vector<std::vector<float>> mat1{
        {1, 5},
        {-3, 2}};
    float answer = 17.f;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float result = Ray_Tracer::Matrix3D<float>::calculate_determinant(matrix1);
    EXPECT_NEAR(answer, result, 0.0001);
}

TEST(Matrix3D, GetSubmatrix1)
{
    std::vector<std::vector<float>> mat1{
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3}};

    std::vector<std::vector<float>> answer{
        {-3, 2},
        {0, 6}};

    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> answer_matrix{answer};

    Ray_Tracer::Matrix3D<float> result = Ray_Tracer::Matrix3D<float>::get_submatrix(matrix1, 0, 2);
    bool eq = (answer_matrix == result);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, GetSubmatrix2)
{
    std::vector<std::vector<float>> mat1{
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1}
        };

    std::vector<std::vector<float>> answer{
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1}
    };

    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> answer_matrix{answer};

    Ray_Tracer::Matrix3D<float> result = Ray_Tracer::Matrix3D<float>::get_submatrix(matrix1, 2, 1);
    bool eq = (answer_matrix == result);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, Minor1){
    std::vector<std::vector<float>> mat1{
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}};
    float answer = 25.f;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float minor = Ray_Tracer::Matrix3D<float>::calculate_minor(mat1, 1, 0);

    EXPECT_NEAR(answer, minor, 0.0001);
}

TEST(Matrix3D, Cofactor1)
{
    std::vector<std::vector<float>> mat1{
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}};
    float answer = -12.f;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float minor1 = Ray_Tracer::Matrix3D<float>::calculate_minor(mat1, 0, 0);
    float cofactor = Ray_Tracer::Matrix3D<float>::calculate_cofactor(mat1, 0, 0);

    EXPECT_NEAR(answer, cofactor, 0.0001);
}

TEST(Matrix3D, Cofacto2)
{
    std::vector<std::vector<float>> mat1{
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}};
    float answer = -25.f;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float minor1 = Ray_Tracer::Matrix3D<float>::calculate_minor(mat1, 1, 0);
    float cofactor = Ray_Tracer::Matrix3D<float>::calculate_cofactor(mat1, 1, 0);

    EXPECT_NEAR(answer, cofactor, 0.0001);
}

TEST(Matrix3D, DeterminantCofactorLargeMatrix1)
{
    std::vector<std::vector<float>> mat1{
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}};
    float answer = 56.f;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float cofactor = Ray_Tracer::Matrix3D<float>::calculate_cofactor(mat1, 0, 0);

    EXPECT_NEAR(answer, cofactor, 0.0001);
}

TEST(Matrix3D, DeterminantCofactorLargeMatrix2)
{
    std::vector<std::vector<float>> mat1{
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}};
    float answer = 12.f;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float cofactor = Ray_Tracer::Matrix3D<float>::calculate_cofactor(mat1, 0, 1);

    EXPECT_NEAR(answer, cofactor, 0.0001);
}

TEST(Matrix3D, DeterminantCofactorLargeMatrix3)
{
    std::vector<std::vector<float>> mat1{
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}};
    float answer = -46;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float cofactor = Ray_Tracer::Matrix3D<float>::calculate_cofactor(mat1, 0, 2);

    EXPECT_NEAR(answer, cofactor, 0.0001);
}

TEST(Matrix3D, DeterminantCofactorLargeMatrix4)
{
    std::vector<std::vector<float>> mat1{
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}};
    float answer = -196;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float determinant = Ray_Tracer::Matrix3D<float>::calculate_determinant(mat1);

    EXPECT_NEAR(answer, determinant, 0.0001);
}

TEST(Matrix3D, DeterminantCofactorLargeMatrix5)
{
    std::vector<std::vector<float>> mat1{
        {-2, -8, 3, 5},
        {-3, 1, 7,  3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}
    };
    float answer = 690;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float cofactor = Ray_Tracer::Matrix3D<float>::calculate_cofactor(mat1, 0, 0);

    EXPECT_NEAR(answer, cofactor, 0.0001);
}

TEST(Matrix3D, DeterminantCofactorLargeMatrix6)
{
    std::vector<std::vector<float>> mat1{
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}};
    float answer = 447;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float cofactor = Ray_Tracer::Matrix3D<float>::calculate_cofactor(mat1, 0, 1);

    EXPECT_NEAR(answer, cofactor, 0.0001);
}

TEST(Matrix3D, DeterminantCofactorLargeMatrix7)
{
    std::vector<std::vector<float>> mat1{
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}};
    float answer = 210;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float cofactor = Ray_Tracer::Matrix3D<float>::calculate_cofactor(mat1, 0, 2);

    EXPECT_NEAR(answer, cofactor, 0.0001);
}

TEST(Matrix3D, DeterminantCofactorLargeMatrix8)
{
    std::vector<std::vector<float>> mat1{
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}};
    float answer = 51;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float cofactor = Ray_Tracer::Matrix3D<float>::calculate_cofactor(mat1, 0, 3);

    EXPECT_NEAR(answer, cofactor, 0.0001);
}

TEST(Matrix3D, DeterminantCofactorLargeMatrix9)
{
    std::vector<std::vector<float>> mat1{
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}};
    float answer = -4071;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    float determinant = Ray_Tracer::Matrix3D<float>::calculate_determinant(mat1);

    EXPECT_NEAR(answer, determinant, 0.0001);
}

TEST(Matrix3D, IsInvertible1)
{
    std::vector<std::vector<float>> mat1{
        {6, 4, 4, 4},
        {5, 5, 7, 6},
        {4, -9, 3, -7},
        {9, 1, 7, -6}
    };
    bool answer = true;
    float determinant_answer = -2120;
    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    bool result = matrix1.is_invertible();

    float determinant = Ray_Tracer::Matrix3D<float>::calculate_determinant(matrix1);

    EXPECT_NEAR(determinant_answer, determinant, 0.001);
    EXPECT_EQ(answer, result);

}

TEST(Matrix3D, IsInvertible2)
{
    std::vector<std::vector<float>> mat1{
        {-4,  2, -2,  -3},
        { 9,  6,  2,   6},
        { 0, -5,  1,  -6},
        { 0,  0,  0,   0}};
    bool answer = false;
    float determinant_answer = 0;

    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    bool result = matrix1.is_invertible();
    float determinant = Ray_Tracer::Matrix3D<float>::calculate_determinant(matrix1);

    EXPECT_NEAR(determinant_answer, determinant, 0.001);
    EXPECT_EQ(answer, result);
}

TEST(Matrix3D, Inverse1)
{
    std::vector<std::vector<float>> mat1{
        {-5, 2,  6, -8},
        {1, -5,  1,  8},
        {7,  7, -6, -7},
        {1, -3,  7,  4}};

    std::vector<std::vector<float>> answer{
        {0.21805, 0.45113, 0.24060, -0.04511},
        {-0.80827, -1.45677, -0.44361, 0.52068},
        {-0.07895, -0.22368, -0.05263, 0.19737},
        {-0.52256, -0.81391, -0.30075, 0.30639}};

    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> answer_matrix1{answer};

    Ray_Tracer::Matrix3D<float> matrix1_inverse = matrix1.get_inverse();

    bool eq = (answer_matrix1 == matrix1_inverse);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, Inverse2)
{
    std::vector<std::vector<float>> mat1{
        {8, -5, 9, 2},
        {7,  5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0,-9,-4}};

    std::vector<std::vector<float>> answer{
        {-0.15385, -0.15385, -0.28205, -0.53846},
        {-0.07692, 0.12308, 0.02564, 0.03077},
        {0.35897, 0.35897, 0.43590, 0.92308},
        {-0.69231, -0.69231, -0.76923, -1.92308}};

    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> answer_matrix1{answer};

    Ray_Tracer::Matrix3D<float> matrix1_inverse = matrix1.get_inverse();

    bool eq = (answer_matrix1 == matrix1_inverse);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, Inverse3)
{
    std::vector<std::vector<float>> mat1{
        {9,   3,  0,  9},
        {-5, -2, -6, -3},
        {-4,  9,  6,  4},
        {-7,  6,  6,  2}};

    std::vector<std::vector<float>> answer{
        {-0.04074, -0.07778, 0.14444, -0.22222},
        {-0.07778, 0.03333, 0.36667, -0.33333},
        {-0.02901, -0.14630, -0.10926, 0.12963},
        {0.17778, 0.06667, -0.26667, 0.33333}};

    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> answer_matrix1{answer};

    Ray_Tracer::Matrix3D<float> matrix1_inverse = matrix1.get_inverse();

    bool eq = (answer_matrix1 == matrix1_inverse);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, InverseReverse)
{
    std::vector<std::vector<float>> mat1{
        { 3, -9,  7,  3},
        { 3, -8,  2, -9},
        {-4,  4,  4,  1},
        {-6,  5, -1,  1}};

    std::vector<std::vector<float>> mat2{
        { 8,  2,  2,  2},
        {-3, -1,  7,  0},
        { 7,  0,  5,  4},
        { 6, -2,  0,  5}};

    Ray_Tracer::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D<float> matrix2{mat2};

    Ray_Tracer::Matrix3D<float> matrix3 = matrix1 * matrix2;
    Ray_Tracer::Matrix3D<float> results = matrix3 * matrix2.get_inverse();

    bool eq = (results == matrix1);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, Translation1){
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::translate(5, -3, 2);
    Ray_Tracer::Tuple3D<float> p{-3, 4, 5, 1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, 2, 0.001);
    EXPECT_NEAR(new_point.y, 1, 0.001);
    EXPECT_NEAR(new_point.z, 7, 0.001);
}

TEST(Matrix3D, Translation2)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::translate(5, -3, 2);
    Ray_Tracer::Matrix3D<float> inverse_transform = transform.get_inverse();
    Ray_Tracer::Tuple3D<float> point{-3, 4, 5, 1};
    Ray_Tracer::Tuple3D<float> new_point = inverse_transform * point;
    EXPECT_NEAR(new_point.x, -8, 0.001);
    EXPECT_NEAR(new_point.y, 7, 0.001);
    EXPECT_NEAR(new_point.z, 3, 0.001);
}

TEST(Matrix3D, Translation3)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::translate(5, -3, 2);
    Ray_Tracer::Vec3D<float> vec{-3, 4, 5};
    Ray_Tracer::Vec3D<float> new_point = transform * vec;
    EXPECT_NEAR(new_point.x, -3, 0.001);
    EXPECT_NEAR(new_point.y, 4, 0.001);
    EXPECT_NEAR(new_point.z, 5, 0.001);
}

TEST(Matrix3D, ScalingPoint)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::scaling(2, 3, 4);
    Ray_Tracer::Tuple3D<float> p{-4, 6, 8};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, -8, 0.001);
    EXPECT_NEAR(new_point.y, 18, 0.001);
    EXPECT_NEAR(new_point.z, 32, 0.001);
}

TEST(Matrix3D, ScalingVector)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::scaling(2, 3, 4);
    Ray_Tracer::Vec3D<float> p{-4, 6, 8};
    Ray_Tracer::Vec3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, -8, 0.001);
    EXPECT_NEAR(new_point.y, 18, 0.001);
    EXPECT_NEAR(new_point.z, 32, 0.001);
}

TEST(Matrix3D, ScalingInverse)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::scaling(2, 3, 4);
    Ray_Tracer::Matrix3D<float> transform_inverse = transform.get_inverse();

    Ray_Tracer::Vec3D<float> v{-4, 6, 8};
    Ray_Tracer::Vec3D<float> new_point = transform_inverse * v;
    EXPECT_NEAR(new_point.x, -2, 0.001);
    EXPECT_NEAR(new_point.y,  2, 0.001);
    EXPECT_NEAR(new_point.z,  2, 0.001);
}

TEST(Matrix3D, ScalingReflection)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::scaling(-1, 1, 1);

    Ray_Tracer::Tuple3D<float> p{2, 3, 4, 1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, -2, 0.001);
    EXPECT_NEAR(new_point.y, 3, 0.001);
    EXPECT_NEAR(new_point.z, 4, 0.001);
}

TEST(Matrix3D, RotationX1)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::rotation_x( pi / 4.f);

    Ray_Tracer::Tuple3D<float> p{0,1,0,1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, 0, 0.001);
    EXPECT_NEAR(new_point.y, std::sqrt(2) / 2.f, 0.001);
    EXPECT_NEAR(new_point.z, std::sqrt(2) / 2.f, 0.001);
}

TEST(Matrix3D, RotationX2)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::rotation_x(pi / 2.f);

    Ray_Tracer::Tuple3D<float> p{0,1,0,1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, 0, 0.001);
    EXPECT_NEAR(new_point.y, 0, 0.001);
    EXPECT_NEAR(new_point.z, 1, 0.001);
}

TEST(Matrix3D, RotationXInverse)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::rotation_x(pi / 4.f);

    Ray_Tracer::Tuple3D<float> p{0,1,0,1};
    Ray_Tracer::Matrix3D<float> transform_inverse = transform.get_inverse();
    Ray_Tracer::Tuple3D<float> new_point = transform_inverse * p;
    EXPECT_NEAR(new_point.x, 0, 0.001);
    EXPECT_NEAR(new_point.y, std::sqrt(2) / 2.f, 0.001);
    EXPECT_NEAR(new_point.z, -std::sqrt(2) / 2.f, 0.001);
}

TEST(Matrix3D, RotationY1)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::rotation_y(pi / 4.f);

    Ray_Tracer::Tuple3D<float> p{0,0,1,1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, std::sqrt(2) / 2.f, 0.001);
    EXPECT_NEAR(new_point.y, 0, 0.001);
    EXPECT_NEAR(new_point.z, std::sqrt(2) / 2.f, 0.001);
}

TEST(Matrix3D, RotationY2)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::rotation_y(pi / 2.f);

    Ray_Tracer::Tuple3D<float> p{0,0,1,1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, 1, 0.001);
    EXPECT_NEAR(new_point.y, 0, 0.001);
    EXPECT_NEAR(new_point.z, 0, 0.001);
}

TEST(Matrix3D, RotationZ1)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::rotation_z(pi / 4.f);

    Ray_Tracer::Tuple3D<float> p{0,1,0,1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, -std::sqrt(2) / 2.f, 0.001);
    EXPECT_NEAR(new_point.y, std::sqrt(2) / 2.f, 0.001);
    EXPECT_NEAR(new_point.z, 0, 0.001);
}

TEST(Matrix3D, RotationZ2)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::rotation_z(pi / 2.f);

    Ray_Tracer::Tuple3D<float> p{0,1,0,1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, -1, 0.001);
    EXPECT_NEAR(new_point.y, 0, 0.001);
    EXPECT_NEAR(new_point.z, 0, 0.001);
}

TEST(Matrix3D, ShearingXY)
{
    Ray_Tracer::Matrix3D<float> transform = 
            Ray_Tracer::Matrix3D<float>::shearing(1,0,0,0,0,0);

    Ray_Tracer::Tuple3D<float> p{2,3,4,1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, 5, 0.001);
    EXPECT_NEAR(new_point.y, 3, 0.001);
    EXPECT_NEAR(new_point.z, 4, 0.001);
}

TEST(Matrix3D, ShearingXZ)
{
    Ray_Tracer::Matrix3D<float> transform = 
                Ray_Tracer::Matrix3D<float>::shearing(0, 1, 0, 0, 0, 0);

    Ray_Tracer::Tuple3D<float> p{2,3,4,1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, 6, 0.001);
    EXPECT_NEAR(new_point.y, 3, 0.001);
    EXPECT_NEAR(new_point.z, 4, 0.001);
}

TEST(Matrix3D, ShearingYX)
{
    Ray_Tracer::Matrix3D<float> transform = 
                Ray_Tracer::Matrix3D<float>::shearing(0, 0, 1, 0, 0, 0);

    Ray_Tracer::Tuple3D<float> p{2, 3, 4, 1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, 2, 0.001);
    EXPECT_NEAR(new_point.y, 5, 0.001);
    EXPECT_NEAR(new_point.z, 4, 0.001);
}

TEST(Matrix3D, ShearingYZ)
{
    Ray_Tracer::Matrix3D<float> transform =
        Ray_Tracer::Matrix3D<float>::shearing(0, 0, 0, 1, 0, 0);

    Ray_Tracer::Tuple3D<float> p{2, 3, 4, 1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, 2, 0.001);
    EXPECT_NEAR(new_point.y, 7, 0.001);
    EXPECT_NEAR(new_point.z, 4, 0.001);
}

TEST(Matrix3D, ShearingZX)
{
    Ray_Tracer::Matrix3D<float> transform =
        Ray_Tracer::Matrix3D<float>::shearing(0, 0, 0, 0, 1, 0);

    Ray_Tracer::Tuple3D<float> p{2, 3, 4, 1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, 2, 0.001);
    EXPECT_NEAR(new_point.y, 3, 0.001);
    EXPECT_NEAR(new_point.z, 6, 0.001);
}

TEST(Matrix3D, ShearingZY)
{
    Ray_Tracer::Matrix3D<float> transform =
        Ray_Tracer::Matrix3D<float>::shearing(0, 0, 0, 0, 0, 1);

    Ray_Tracer::Tuple3D<float> p{2, 3, 4, 1};
    Ray_Tracer::Tuple3D<float> new_point = transform * p;
    EXPECT_NEAR(new_point.x, 2, 0.001);
    EXPECT_NEAR(new_point.y, 3, 0.001);
    EXPECT_NEAR(new_point.z, 7, 0.001);
}

TEST(Matrix3D, Chaining1){
    Ray_Tracer::Tuple3D<float> p{1, 0, 1};
    Ray_Tracer::Matrix3D<float> A =
        Ray_Tracer::Matrix3D<float>::rotation_x( pi / 2.f );
    Ray_Tracer::Matrix3D<float> B =
        Ray_Tracer::Matrix3D<float>::scaling(5,5,5);
    Ray_Tracer::Matrix3D<float> C =
        Ray_Tracer::Matrix3D<float>::translate(10, 5, 7);

    Ray_Tracer::Tuple3D<float> p2{1, -1, 0};
    Ray_Tracer::Tuple3D<float> p2_results = A * p;
    EXPECT_NEAR(p2_results.x, p2.x, 0.001);
    EXPECT_NEAR(p2_results.y, p2.y, 0.001);
    EXPECT_NEAR(p2_results.z, p2.z, 0.001);

    Ray_Tracer::Tuple3D<float> p3{5, -5, 0};
    Ray_Tracer::Tuple3D<float> p3_results = B * p2;
    EXPECT_NEAR(p3_results.x, p3.x, 0.001);
    EXPECT_NEAR(p3_results.y, p3.y, 0.001);
    EXPECT_NEAR(p3_results.z, p3.z, 0.001);

    Ray_Tracer::Tuple3D<float> p4{15, 0, 7};
    Ray_Tracer::Tuple3D<float> p4_results = C * p3;
    EXPECT_NEAR(p4_results.x, p4.x, 0.001);
    EXPECT_NEAR(p4_results.y, p4.y, 0.001);
    EXPECT_NEAR(p4_results.z, p4.z, 0.001);

    Ray_Tracer::Matrix3D<float> T = C * B * A;
    Ray_Tracer::Tuple3D<float> answer{15, 0, 7};
    Ray_Tracer::Tuple3D<float> results = T * p;

    EXPECT_NEAR(answer.x, results.x, 0.001);
    EXPECT_NEAR(answer.y, results.y, 0.001);
    EXPECT_NEAR(answer.z, results.z, 0.005);
}