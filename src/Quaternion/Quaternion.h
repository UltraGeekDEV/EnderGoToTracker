#pragma once
#include "../Vector3/Vector3.h"

class Quaternion{
public:
double w,x,y,z;
static Quaternion Euler(double x,double y,double z);
Quaternion(double _w,double _x,double _y,double _z):w(_w),x(_x),y(_y),z(_z){}
Quaternion():w(1),x(0),y(0),z(0){}
Quaternion operator*(const Quaternion& q2);
Quaternion operator*(const Vector3& q2);
Quaternion Inverse();
};