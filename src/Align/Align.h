#pragma once
#include "../Axis/Axis.h"
#include "../Quaternion/Quaternion.h"

class Align{
private:
    double ra;
    double dec;
    Axis RaAxis;
    Axis DecAxis;
    Quaternion toWorldQuat;
    void FindPole(float& x,float& y,float& z,float tileSize,float tileResolution);
    
public:
    void GoTo(double ra,double dec);
    void Sync(double ra,double dec);
    void ClearAlign();
};