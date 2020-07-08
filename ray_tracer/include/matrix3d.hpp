#include <cmath>
#include <iostream>
#include <vector>
#include "./tuple3d.hpp"
#include "./vec3d.hpp"

#pragma once
namespace Ray_Tracer{
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

        void transpose_mutation(){
            Matrix3D<T> transpose_matrix{};
            for(int i=0; i < row; i++){
                for(int j=0; j < col; j++){
                    transpose_matrix.matrix[j][i] = matrix[i][j];
                }
            }
            matrix = transpose_matrix.matrix;
        }

        Matrix3D<T> transpose()
        {
            Matrix3D<T> transpose_matrix{};
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    transpose_matrix.matrix[j][i] = matrix[i][j];
                }
            }
            return transpose_matrix;
        }

        bool is_invertible()
        {
            if(Matrix3D::calculate_determinant(matrix) == 0){
                return false;
            }else{
                return true;
            }
        }

        Matrix3D<T> get_inverse(){
            if(!is_invertible()){
                return *this;
            }

            Matrix3D cofactor_matrix{};
            for(int i=0; i<row; i++){
                for(int j=0; j<col; j++){
                    cofactor_matrix.matrix[i][j] = calculate_cofactor( matrix, i, j );
                }
            }

            cofactor_matrix = cofactor_matrix.transpose();
            float determinant = calculate_determinant(*this);
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    cofactor_matrix.matrix[i][j] /= determinant;
                }
            }
            return cofactor_matrix;
        }

        static T calculate_determinant(Matrix3D<T> mat)
        {

            T determinant = 0.0;
            if(mat.row == 2 && mat.col == 2){
                determinant = (mat.matrix[0][0] * mat.matrix[1][1]) - (mat.matrix[0][1] * mat.matrix[1][0]);
            }else{
                for (int i = 0; i < mat.col; i++)
                {
                    T cofactor = Matrix3D::calculate_cofactor(mat, 0, i);
                    determinant += (cofactor * mat.matrix[0][i]);
                }
            }
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

        static T calculate_minor(const Matrix3D<T> mat, int row, int col)
        {
            Matrix3D<float> b = get_submatrix(mat, row, col);
            float minor = Matrix3D<float>::calculate_determinant(b);
            return minor;
        }

        static T calculate_cofactor(const Matrix3D<T> mat, int row, int col)
        {
            T minor = calculate_minor(mat, row, col);
            if((row + col) % 2 == 1){
                return -1 * minor;
            }else{
                return minor;
            }
        }

        static Matrix3D<T> get_generic_identity_matrix(){
            std::vector<std::vector<float>> id_mat{
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}};
            Matrix3D<T> id_matrix { id_mat };
            return id_matrix;
        }

        static Matrix3D<T> translate(T x, T y, T z){
            Matrix3D<T> tranlate_matrix = get_generic_identity_matrix();
            tranlate_matrix.matrix[0][3] = x;
            tranlate_matrix.matrix[1][3] = y;
            tranlate_matrix.matrix[2][3] = z;
            tranlate_matrix.matrix[3][3] = 1;
            return tranlate_matrix;
        }

        static Matrix3D<T> scaling(T x, T y, T z)
        {
            Matrix3D<T> tranlate_matrix = get_generic_identity_matrix();
            tranlate_matrix.matrix[0][0] = x;
            tranlate_matrix.matrix[1][1] = y;
            tranlate_matrix.matrix[2][2] = z;
            tranlate_matrix.matrix[3][3] = 1;
            return tranlate_matrix;
        }

        static Matrix3D<T> rotation_x(float radians)
        {
            Matrix3D<T> tranlate_matrix = get_generic_identity_matrix();
            tranlate_matrix.matrix[1][1] =  std::cos(radians);
            tranlate_matrix.matrix[1][2] = -std::sin(radians);
            tranlate_matrix.matrix[2][1] =  std::sin(radians);
            tranlate_matrix.matrix[2][2] =  std::cos(radians);
            return tranlate_matrix;
        }

        static Matrix3D<T> rotation_y(float radians)
        {
            Matrix3D<T> tranlate_matrix = get_generic_identity_matrix();
            tranlate_matrix.matrix[0][0] = std::cos(radians);
            tranlate_matrix.matrix[0][2] = std::sin(radians);
            tranlate_matrix.matrix[2][0] = -std::sin(radians);
            tranlate_matrix.matrix[2][2] = std::cos(radians);
            return tranlate_matrix;
        }

        static Matrix3D<T> rotation_z(float radians)
        {
            Matrix3D<T> tranlate_matrix = get_generic_identity_matrix();
            tranlate_matrix.matrix[0][0] = std::cos(radians);
            tranlate_matrix.matrix[0][1] = -std::sin(radians);
            tranlate_matrix.matrix[1][0] = std::sin(radians);
            tranlate_matrix.matrix[1][1] = std::cos(radians);
            return tranlate_matrix;
        }

        static Matrix3D<T> shearing(T xy, T xz, T yx, T yz, T zx, T zy)
        {
            Matrix3D<T> tranlate_matrix = get_generic_identity_matrix();
            tranlate_matrix.matrix[0][1] = xy;
            tranlate_matrix.matrix[0][2] = xz;
            tranlate_matrix.matrix[1][0] = yx;
            tranlate_matrix.matrix[1][2] = yz;
            tranlate_matrix.matrix[2][0] = zx;
            tranlate_matrix.matrix[2][1] = zy;
            return tranlate_matrix;
        }
    };

    template <typename T>
    bool isEqual(T x, T y)
    {
        const T epsilon = 0.01/* some small number such as 1e-5 */;
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
    Ray_Tracer::Tuple3D<T> operator*(const Matrix3D<T> &A, const Ray_Tracer::Tuple3D<T> &B)
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
        Ray_Tracer::Tuple3D<T> ret { C[0], C[1], C[2], C[3] };
        return ret;
    }

    template <typename T>
    Ray_Tracer::Vec3D<T> operator*(const Matrix3D<T> &A, const Ray_Tracer::Vec3D<T> &B)
    {

        std::vector<T> C{};

        for (int i = 0; i < A.row; i++)
        {
            T result = 0;
            for (int j = 0; j < B.size; j++)
            {
                float tmp = (A.matrix[i][j] * B.getValueByIndex(j));
                result += tmp;
            }
            C.push_back(result);
        }
        Ray_Tracer::Vec3D<T> ret{C[0], C[1], C[2]};
        return ret;
    }
}