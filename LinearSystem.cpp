#include "LinearSystem.hpp"
#include <cmath>
LinearSystem::LinearSystem(const Matrix& A,const Vector& b): mSize(A.Rows()), mA(A), mb(b){ assert(A.Rows()==A.Cols() && A.Rows()==b.Size()); }
Vector LinearSystem::Solve() const{
    Matrix M(mA); Vector v(mb);
    for(int k=1;k<=mSize;++k){ int imax=k; double amax=std::fabs(M(k,k)); for(int i=k+1;i<=mSize;++i){ double a=std::fabs(M(i,k)); if(a>amax){amax=a; imax=i;} }
        assert(amax>0.0 && "Singular matrix"); if(imax!=k){ for(int j=k;j<=mSize;++j) std::swap(M(k,j),M(imax,j)); std::swap(v(k),v(imax)); }
        for(int i=k+1;i<=mSize;++i){ double factor=M(i,k)/M(k,k); M(i,k)=0; for(int j=k+1;j<=mSize;++j) M(i,j)-=factor*M(k,j); v(i)-=factor*v(k); }
    }
    Vector x(mSize); for(int i=mSize;i>=1;--i){ double sum=v(i); for(int j=i+1;j<=mSize;++j) sum-=M(i,j)*x(j); x(i)=sum/M(i,i); } return x; }
Vector PosSymLinSystem::Solve() const{
    const int n=mSize; const double tol=1e-10; const int maxIt=5*n; Vector x(n); Vector r=mb-mA*x; Vector p=r; double rsold=r*r;
    for(int it=0;it<maxIt;++it){ Vector Ap=mA*p; double alpha=rsold/(p*Ap); x+=alpha*p; r-=alpha*Ap; double rsnew=r*r; if(std::sqrt(rsnew)<tol) break; p=r+(rsnew/rsold)*p; rsold=rsnew; }
    return x;}