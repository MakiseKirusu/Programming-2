#include "Matrix.hpp"
#include <cassert>
#include <cmath>
#include <vector>
Matrix::Matrix(int r,int c):mRows(r),mCols(c),mData(new double[r*c]()){ std::fill(mData,mData+r*c,0.0); }
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> init): Matrix((int)init.size(),(int)init.begin()->size()){
    int i=1; for(auto& row:init){ int j=1; for(double v:row)(*this)(i,j++)=v; ++i; }
}
Matrix::Matrix(const Matrix& o): Matrix(o.mRows,o.mCols){ std::copy(o.mData,o.mData+mRows*mCols,mData); }
Matrix::~Matrix(){ delete[] mData; }
Matrix& Matrix::operator=(const Matrix& rhs){ if(this==&rhs) return *this; if(mRows*mCols!=rhs.mRows*rhs.mCols){ delete[] mData; mData=new double[rhs.mRows*rhs.mCols]; } mRows=rhs.mRows; mCols=rhs.mCols; std::copy(rhs.mData,rhs.mData+mRows*mCols,mData); return *this; }
double& Matrix::operator()(int i,int j){ assert(i>=1&&i<=mRows&&j>=1&&j<=mCols); return mData[Index(i,j)]; }
const double& Matrix::operator()(int i,int j) const{ assert(i>=1&&i<=mRows&&j>=1&&j<=mCols); return mData[Index(i,j)]; }
Matrix Matrix::operator+() const{ return *this; }
Matrix Matrix::operator-() const{ Matrix t(*this); for(int k=0;k<mRows*mCols;++k) t.mData[k]=-t.mData[k]; return t; }
Matrix& Matrix::operator+=(const Matrix& r){ assert(mRows==r.mRows&&mCols==r.mCols); for(int k=0;k<mRows*mCols;++k) mData[k]+=r.mData[k]; return *this; }
Matrix& Matrix::operator-=(const Matrix& r){ assert(mRows==r.mRows&&mCols==r.mCols); for(int k=0;k<mRows*mCols;++k) mData[k]-=r.mData[k]; return *this; }
Matrix& Matrix::operator*=(double a){ for(int k=0;k<mRows*mCols;++k) mData[k]*=a; return *this; }
static void LUDecompose(Matrix& A,std::vector<int>& piv,double& detSign){
    int n=A.Rows(); piv.resize(n+1); detSign=1.0; for(int i=1;i<=n;++i) piv[i]=i;
    for(int k=1;k<=n;++k){
        int imax=k; double amax=std::fabs(A(k,k));
        for(int i=k+1;i<=n;++i){ double a=std::fabs(A(i,k)); if(a>amax){amax=a; imax=i;} }
        assert(amax>0.0 && "Singular matrix");
        if(imax!=k){ detSign=-detSign; for(int j=1;j<=n;++j) std::swap(A(k,j),A(imax,j)); std::swap(piv[k],piv[imax]); }
        for(int i=k+1;i<=n;++i){ A(i,k)/=A(k,k); for(int j=k+1;j<=n;++j) A(i,j)-=A(i,k)*A(k,j); }
    }
}
double Matrix::Determinant() const{ assert(mRows==mCols); Matrix LU(*this); std::vector<int> piv; double sign; LUDecompose(LU,piv,sign); double det=sign; for(int i=1;i<=mRows;++i) det*=LU(i,i); return det; }
Matrix Matrix::Inverse() const{ assert(mRows==mCols); int n=mRows; Matrix LU(*this); std::vector<int> piv; double sign; LUDecompose(LU,piv,sign); Matrix inv(n,n);
    for(int col=1; col<=n; ++col){ Vector e(n); e(col)=1.0; Vector y(n);
        for(int i=1;i<=n;++i){ double s=e(piv[i]); for(int j=1;j<i;++j) s-=LU(i,j)*y(j); y(i)=s; }
        Vector x(n); for(int i=n;i>=1;--i){ double s=y(i); for(int j=i+1;j<=n;++j) s-=LU(i,j)*x(j); x(i)=s/LU(i,i);} for(int i=1;i<=n;++i) inv(i,col)=x(i); }
    return inv;}
Matrix Matrix::PseudoInverse(double lambda) const{
    Matrix At(mCols, mRows);
    for (int i = 1; i <= mRows; ++i)
        for (int j = 1; j <= mCols; ++j)
            At(j, i) = (*this)(i, j);
    Matrix AtA = At * (*this);
    if (lambda > 0.0)
        for (int i = 1; i <= AtA.Rows(); ++i)
            AtA(i, i) += lambda;

    return AtA.Inverse() * At;
}
Vector operator*(const Matrix& A, const Vector& x){
    assert(A.Cols() == x.Size());
    Vector y(A.Rows());
    for (int i = 1; i <= A.Rows(); ++i) {
        double sum = 0.0;
        for (int j = 1; j <= A.Cols(); ++j) sum += A(i, j) * x(j);
        y(i) = sum;
    }
    return y;
}
Matrix operator*(const Matrix& A, const Matrix& B){
    assert(A.Cols() == B.mRows);
    Matrix C(A.mRows, B.mCols);               
    for (int i = 1; i <= C.Rows(); ++i)
        for (int k = 1; k <= A.Cols(); ++k) {
            double a = A(i, k);
            for (int j = 1; j <= C.Cols(); ++j) C(i, j) += a * B(k, j);
        }
    return C;
}
