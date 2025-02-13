#include "./Vector3.h"

double Vector3::Dot(const Vector3& b){
    return x*b.x+y*b.y+z*b.z;
}