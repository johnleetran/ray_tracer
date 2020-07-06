#include <gtest/gtest.h> // googletest header file

#include <string>
#include <cmath>
#include <vector>

#include "matrix3d.hpp"

TEST(Matrix3D, Create2x2)
{
    std::vector<std::vector<float>> mat{
        {-3, 5},
        {1, -2}};
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix{mat};
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
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix{mat};
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
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix{mat};
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
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix2{mat2};
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
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix2{mat2};
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
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix2{mat2};
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

    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix2{mat2};

    Ray_Tracer::Matrix3D::Matrix3D<float> result = matrix1 * matrix2;
    Ray_Tracer::Matrix3D::Matrix3D<float> answer_matrix{answer};

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
    Ray_Tracer::Tuple3D::Tuple3D<float> tup{1, 2, 3, 1};

    Ray_Tracer::Tuple3D::Tuple3D<float> answer{18, 24, 33, 1};

    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};

    Ray_Tracer::Tuple3D::Tuple3D<float> result = matrix1 * tup;

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

    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix2{mat2};

    Ray_Tracer::Matrix3D::Matrix3D<float> result = matrix1 * matrix2;

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

    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D::Matrix3D<float> answer_matrix{answer};

    matrix1.transpose();

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

    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D::Matrix3D<float> answer_matrix{answer};

    matrix1.transpose();

    bool eq = (answer_matrix == matrix1);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, CalculateDeterminant2x2)
{
    std::vector<std::vector<float>> mat1{
        {1, 5},
        {-3, 2}};
    float answer = 17.f;
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    float result = Ray_Tracer::Matrix3D::Matrix3D<float>::calculate_determinant(matrix1);
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

    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D::Matrix3D<float> answer_matrix{answer};

    Ray_Tracer::Matrix3D::Matrix3D<float> result = Ray_Tracer::Matrix3D::Matrix3D<float>::get_submatrix(matrix1, 0, 2);
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

    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    Ray_Tracer::Matrix3D::Matrix3D<float> answer_matrix{answer};

    Ray_Tracer::Matrix3D::Matrix3D<float> result = Ray_Tracer::Matrix3D::Matrix3D<float>::get_submatrix(matrix1, 2, 1);
    bool eq = (answer_matrix == result);
    EXPECT_EQ(eq, true);
}

TEST(Matrix3D, Minor1){
    std::vector<std::vector<float>> mat1{
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}};
    float answer = 25.f;
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    float minor = Ray_Tracer::Matrix3D::Matrix3D<float>::calculate_minor(mat1, 1, 0);

    EXPECT_NEAR(answer, minor, 0.0001);
}

TEST(Matrix3D, Cofactor1)
{
    std::vector<std::vector<float>> mat1{
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}};
    float answer = -12.f;
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    float minor1 = Ray_Tracer::Matrix3D::Matrix3D<float>::calculate_minor(mat1, 0, 0);
    float cofactor = Ray_Tracer::Matrix3D::Matrix3D<float>::calculate_cofactor(mat1, 0, 0);

    EXPECT_NEAR(answer, cofactor, 0.0001);
}

TEST(Matrix3D, Cofacto2)
{
    std::vector<std::vector<float>> mat1{
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}};
    float answer = -25.f;
    Ray_Tracer::Matrix3D::Matrix3D<float> matrix1{mat1};
    float minor1 = Ray_Tracer::Matrix3D::Matrix3D<float>::calculate_minor(mat1, 1, 0);
    float cofactor = Ray_Tracer::Matrix3D::Matrix3D<float>::calculate_cofactor(mat1, 1, 0);

    EXPECT_NEAR(answer, cofactor, 0.0001);
}