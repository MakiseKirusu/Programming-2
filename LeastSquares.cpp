#include "LeastSquares.hpp"
Vector SolveLeastSquares(const Matrix& X,const Vector& y,double lambda){
    return X.PseudoInverse(lambda) * y;
}