#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP
#include "Matrix.hpp"
class LinearSystem{
protected:
    int    mSize;
    Matrix mA;
    Vector mb;
public:
    LinearSystem(const Matrix& A, const Vector& b);
    virtual ~LinearSystem() = default;
    virtual Vector Solve() const;             
private:
    LinearSystem() = delete;
    LinearSystem(const LinearSystem&) = delete;
    LinearSystem& operator=(const LinearSystem&) = delete;
};
class PosSymLinSystem : public LinearSystem {
public:
    using LinearSystem::LinearSystem;
    Vector Solve() const override;              
};
#endif 
