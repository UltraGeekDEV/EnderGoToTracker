#pragma once
#include "./Quaternion/Quaternion.h"

Vector3 GetCarthesian(Vector3 polar){
    polar.x *= Deg2Rad;
    polar.y *= Deg2Rad;

    return Vector3(cos(polar.y)*sin(polar.x),sin(polar.y),cos(polar.y)*cos(polar.x));
}

Vector3 GetPolar(Vector3 carth){
    return Vector3(atan2(carth.x,carth.z)*Rad2Deg,asin(carth.y)*Rad2Deg,0);
}