#ifndef MATRIX_HPP
#define MATRIX_HPP
#include "Vector.hpp"
class Matrix{
    int mRows, mCols;
    double* mData;               
    int Index(int i,int j) const { return (i-1)*mCols + (j-1); }
public:
    Matrix(int rows,int cols);
    Matrix(std::initializer_list<std::initializer_list<double>> init);
    Matrix(const Matrix& other);
    ~Matrix();
    Matrix& operator=(const Matrix& rhs);
    double& operator()(int i,int j);
    const double& operator()(int i,int j) const;
    int Rows() const { return mRows; }
    int Cols() const { return mCols; }
    Matrix operator+() const;
    Matrix operator-() const;
    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix& operator*=(double a);
    double Determinant() const;
    Matrix Inverse() const;
    Matrix  PseudoInverse(double lambda=0.0) const;
    friend Vector operator*(const Matrix& A,const Vector& x);
    friend Matrix operator*(const Matrix& A,const Matrix& B);
};
#endif