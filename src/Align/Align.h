#pragma once
#include "../Axis/Axis.h"
#include "../Quaternion/Quaternion.h"
#include "vector"
#include "../CPConvert.cpp"

class Align{
private:
    Vector2 totalAngleOffset; 
    Vector2 rates;
    Axis& RaAxis;
    Axis& DecAxis;
    Quaternion toMountQuat;
    int starCount;
    std::vector<Vector3> realCoords;
    std::vector<Vector3> measuredCoords;
    void FindPole(double& x,double& y,double& z,double tileSize,double tileResolution,Quaternion& curBest,double& curBestEval);
    void FindPole();
    double GetEval();
    Vector2 GetMountPos();

public:
    void GoTo(Vector2 pos);
    void Sync(Vector2 pos);
    void Update(double deltaTime);
    void SetConstantRate(Vector2 newRates);
    void ClearAlign();
    Align(Axis& raAxis, Axis& decAxis):RaAxis(raAxis),DecAxis(decAxis),toMountQuat(),realCoords(),measuredCoords(),starCount(0),totalAngleOffset(0,0),rates(360/24.0/60.0f/60.0f,0){}
};