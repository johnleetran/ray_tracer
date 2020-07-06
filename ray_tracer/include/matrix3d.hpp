#include <cmath>
#include <iostream>
#include <vector>
#include "./tuple3d.hpp"
#pragma once
namespace Ray_Tracer{
    namespace Matrix3D{
        template <typename T>
        class Matrix3D{
            public:
            std::vector< std::vector<T> > matrix;
            int row;
            int col;
            Matrix3D(){
                row = 4;
                col = 4;
                for(int i=0; i<row; i++){
                    matrix.push_back(std::vector<T>{});
                    for(int j=0; j<col; j++){
                        matrix[i].push_back(0);
                    }
                }
            }

            Matrix3D(std::vector<std::vector<T>> mat)
            {
                matrix = mat;
                row = mat.size();
                col = mat[0].size();
            }

            void transpose(){
                Matrix3D<T> transpose_matrix{};
                for(int i=0; i < row; i++){
                    for(int j=0; j < col; j++){
                        transpose_matrix.matrix[j][i] = matrix[i][j];
                    }
                }
                matrix = transpose_matrix.matrix;
            }

            static T calculate_determinant(Matrix3D<T> mat){
                T determinant = (mat.matrix[0][0] * mat.matrix[1][1]) - (mat.matrix[0][1] * mat.matrix[1][0]);
                return determinant;
            }

            static Matrix3D<T> get_submatrix(const Matrix3D<T> mat, int remove_row, int remove_col)
            {
                std::vector< std::vector<T> > new_mat{};
                for(int i=0; i < mat.row; i++){
                    if(i == remove_row){
                        continue;
                    }
                    new_mat.push_back(std::vector<T>{});
                    for(int j=0; j < mat.col; j++){
                        if(j == remove_col){
                            continue;
                        }
                        new_mat.back().push_back(mat.matrix[i][j]);
                    }
                }
                Matrix3D<T> tmp{new_mat};
                return tmp;
            }
        };

        template <typename T>
        bool isEqual(T x, T y)
        {
            const T epsilon = 0.00001/* some small number such as 1e-5 */;
            return std::abs(x - y) <= epsilon * std::abs(x);
            // see Knuth section 4.2.2 pages 217-218
        }

        template <typename T>
        bool operator==(const Matrix3D<T> &t1, const Matrix3D<T> &t2)
        {
            bool diff = true;
            if(t1.row != t2.row || t1.col != t2.col){
                return false;
            }

            for(int i=0; i<t1.row; i++){
                for(int j=0; j < t1.col; j++){
                    //float diff = std::abs(t1.matrix[i][j], t2.matrix[i][j]);
                    if (!isEqual(t1.matrix[i][j], t2.matrix[i][j]))
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        template <typename T>
        Matrix3D<T> operator*(const Matrix3D<T> &t1, const Matrix3D<T> &t2)
        {

            Matrix3D<float> ret{};

            for (int i = 0; i < t1.row; i++)
            {
                for (int j = 0; j < t1.col; j++)
                {
                    ret.matrix[i][j] = (t1.matrix[i][0] * t2.matrix[0][j]) +
                                       (t1.matrix[i][1] * t2.matrix[1][j]) +
                                       (t1.matrix[i][2] * t2.matrix[2][j]) +
                                       (t1.matrix[i][3] * t2.matrix[3][j]);
                }
            }
            return ret;
        }

        template <typename T>
        Ray_Tracer::Tuple3D::Tuple3D<T> operator*(const Matrix3D<T> &A, const Ray_Tracer::Tuple3D::Tuple3D<T> &B)
        {

            std::vector<T> C{};

            for(int i=0; i < A.row; i++){
                T result = 0;
                for(int j=0; j < B.size; j++){
                    float tmp = (A.matrix[i][j]  * B.getValueByIndex(j));
                    result += tmp;
                }
                C.push_back(result);
            }
            Ray_Tracer::Tuple3D::Tuple3D<T> ret { C[0], C[1], C[2], C[3] };
            return ret;
        }
    }
}