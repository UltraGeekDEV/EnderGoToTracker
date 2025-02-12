#include "Quaternion.h"

Quaternion Quaternion::Euler(double x,double y,double z){
    Quaternion quat(0,0,0,0);

    
    x *= Deg2Rad;
    y *= Deg2Rad;
    z *= Deg2Rad;
    // Precompute the cos and sin for each angle divided by 2
    float cosX = cos(x / 2);
    float sinX = sin(x / 2);
    float cosY = cos(y / 2);
    float sinY = sin(y / 2);
    float cosZ = cos(z / 2);
    float sinZ = sin(z / 2);
    
    // Calculate the quaternion components
    quat.w = cosX * cosY * cosZ + sinX * sinY * sinZ;
    quat.x = sinX * cosY * cosZ - cosX * sinY * sinZ;
    quat.y = cosX * sinY * cosZ + sinX * cosY * sinZ;
    quat.z = cosX * cosY * sinZ - sinX * sinY * cosZ;
    
    
    return quat;
}

Quaternion Quaternion::operator*(const Quaternion& q2){
    Quaternion result(0,0,0,0);

    result.w = w * q2.w - x * q2.x - y * q2.y - z * q2.z;
    result.x = w * q2.x + x * q2.w + y * q2.z - z * q2.y;
    result.y = w * q2.y - x * q2.z + y * q2.w + z * q2.x;
    result.z = w * q2.z + x * q2.y - y * q2.x + z * q2.w;

    return result;
}

Vector3 Quaternion::operator*(const Vector3& q2){
    Vector3 ret;
    Quaternion v(0,q2.x,q2.y,q2.z);
    auto quatResult = *this * v * Inverse();
    
    ret.x = quatResult.x;
    ret.y = quatResult.y;
    ret.z = quatResult.z;
    
    return ret;
}

Quaternion Quaternion::Inverse(){
    return Quaternion(w,-x,-y,-z);
}