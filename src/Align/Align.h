#pragma once
#include "../Axis/Axis.h"
#include "../Quaternion/Quaternion.h"
#include "vector"

class Align{
private:
    double ra;
    double dec;
    Axis RaAxis;
    Axis DecAxis;
    Quaternion toMountQuat;
    int starCount;
    std::vector<Vector3> realCoords;
    std::vector<Vector3> measuredCoords;
    void FindPole(float& x,float& y,float& z,float tileSize,float tileResolution);

public:
    void GoTo(double ra,double dec);
    void Sync(double ra,double dec);
    void ClearAlign();
    Align(Axis raAxis, Axis decAxis):RaAxis(raAxis),DecAxis(decAxis),ra(0),dec(0),toMountQuat(),realCoords(),measuredCoords(),starCount(0){}
};