#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cassert>
#include <initializer_list>
#include <algorithm>
#include <iostream>
class Vector {
    int mSize;
    double* mData;
    int index(int i) const{return i - 1;}
public:
    explicit Vector(int size);
    Vector(std::initializer_list<double> list);
    Vector(const Vector& other);
    ~Vector();
    Vector& operator=(const Vector& rhs);
    double& operator()(int i);
    const double& operator()(int i) const;
    double& operator[](int i) {return (*this)(i);}
    const double&  operator[](int i) const {return (*this)(i);}
    int Size() const{return mSize;}
    Vector operator+() const;
    Vector operator-() const;
    Vector& operator+=(const Vector& rhs);
    Vector& operator-=(const Vector& rhs);
    Vector& operator*=(double a);
    double operator*(const Vector& rhs) const;
    double SquaredNorm() const;
    void  Swap(Vector& other);
};
Vector operator+(Vector lhs, const Vector& rhs);
Vector operator-(Vector lhs, const Vector& rhs);
Vector operator*(Vector v, double a);
Vector operator*(double a, Vector v);
std::ostream& operator<<(std::ostream& os,const Vector& v);
#endif