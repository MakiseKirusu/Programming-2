#ifndef LEASTSQUARES_HPP
#define LEASTSQUARES_HPP
#include "Matrix.hpp"
Vector SolveLeastSquares(const Matrix& X,const Vector& y,double lambda=0.0);
#endif