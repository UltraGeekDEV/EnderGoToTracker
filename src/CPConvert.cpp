#pragma once
#include "./Quaternion/Quaternion.h"
#include "./Vector2.h"

Vector3 GetCarthesian(Vector2 polar){
    polar.x *= Deg2Rad;
    polar.y *= Deg2Rad;

    return Vector3(cos(polar.y)*sin(polar.x),sin(polar.y),cos(polar.y)*cos(polar.x));
}

Vector2 GetPolar(Vector3 carth){
    return Vector2(atan2(carth.x,carth.z)*Rad2Deg,asin(carth.y)*Rad2Deg);
}