#pragma once

class Vector3{
public:
    double x,y,z;
    Vector3(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
    Vector3():x(0),y(0),z(0){}
    double Dot(const Vector3& b);
};