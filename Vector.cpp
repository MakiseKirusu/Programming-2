#include "Vector.hpp"
Vector::Vector(int size): mSize(size), mData(new double[size]()) {}
Vector::Vector(std::initializer_list<double> list): Vector(static_cast<int>(list.size())) {
    std::copy(list.begin(), list.end(), mData);
}
Vector::Vector(const Vector& o): Vector(o.mSize) {
    std::copy(o.mData,o.mData+mSize,mData);
}
Vector::~Vector(){ delete[] mData; }
Vector& Vector::operator=(const Vector& rhs){
    if(this==&rhs) return *this;
    if(mSize!=rhs.mSize){ delete[] mData; mSize=rhs.mSize; mData=new double[mSize]; }
    std::copy(rhs.mData,rhs.mData+mSize,mData);
    return *this;
}
double& Vector::operator()(int i){ assert(i>=1 && i<=mSize); return mData[index(i)]; }
const double& Vector::operator()(int i) const{ assert(i>=1 && i<=mSize); return mData[index(i)]; }
Vector Vector::operator+() const { return *this; }
Vector Vector::operator-() const { Vector tmp(*this); for(int i=0;i<mSize;++i) tmp.mData[i]=-tmp.mData[i]; return tmp; }
Vector& Vector::operator+=(const Vector& r){ assert(mSize==r.mSize); for(int i=0;i<mSize;++i) mData[i]+=r.mData[i]; return *this; }
Vector& Vector::operator-=(const Vector& r){ assert(mSize==r.mSize); for(int i=0;i<mSize;++i) mData[i]-=r.mData[i]; return *this; }
Vector& Vector::operator*=(double a){ for(int i=0;i<mSize;++i) mData[i]*=a; return *this; }
double Vector::operator*(const Vector& r) const{ assert(mSize==r.mSize); double s=0; for(int i=0;i<mSize;++i) s+=mData[i]*r.mData[i]; return s; }
double Vector::SquaredNorm() const{ return *this * *this; }
void Vector::Swap(Vector& o){ std::swap(mSize,o.mSize); std::swap(mData,o.mData); }
Vector operator+(Vector lhs, const Vector& rhs){ lhs+=rhs; return lhs; }
Vector operator-(Vector lhs, const Vector& rhs){ lhs-=rhs; return lhs; }
Vector operator*(Vector v, double a){ v*=a; return v; }
Vector operator*(double a, Vector v){ v*=a; return v; }
std::ostream& operator<<(std::ostream& os,const Vector& v){ os<<'['; for(int i=1;i<=v.Size();++i) os<<v(i)<<(i==v.Size()?']':' '); return os; }
