#include "LinearSystem.hpp"
#include "LeastSquares.hpp"
#include "Regression.hpp"
#include <iostream>
int main(){
    Matrix A{{ {4,1}, {1,3} }}; Vector b{{1,2}}; PosSymLinSystem sys(A,b); std::cout<<"Ax=b → "<<sys.Solve()<<"\n";
    Matrix X(3,2); X(1,1)=1; X(1,2)=1; X(2,1)=1; X(2,2)=2; X(3,1)=1; X(3,2)=3; Vector y{{1,2,2}}; std::cout<<"β (toy) = "<<SolveLeastSquares(X,y)<<"\n";
    RunPartB();
    return 0;
}