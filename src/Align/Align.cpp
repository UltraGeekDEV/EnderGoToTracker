#include "Align.h"

void Align::FindPole(double& angleX,double& angleY,double& angleZ,double tileSize,double tileResolution,Quaternion& curBest,double& curBestEval){
    double x=0,y=0,z=0;

    double halfTileSize = tileSize * 0.5;
    
    for (double i = -halfTileSize; i < halfTileSize; i+=tileResolution)
    {
        for (double j= -halfTileSize; j < halfTileSize; j+=tileResolution)
        {
            for (double k = -halfTileSize; k < halfTileSize; k+=tileResolution)
            {
                Quaternion checkQuat = Quaternion::Euler(angleX+i,angleY+j,angleZ+k);
                double eval = GetEval();
                if(eval < curBestEval){
                    curBestEval = eval;
                    curBest = checkQuat;
                    x = i;
                    y = j;
                    z = k;
                }
            }
        }
    }

    angleX += x;
    angleY += y;
    angleZ += z;
}

double Align::GetEval(){
    float sum = 0;
    for (int i = 0; i < starCount; i++)
    {
        sum += pow(acos(measuredCoords[i].Dot(toMountQuat * realCoords[i])),2.0);
    }
    return sum;
}

void Align::FindPole(){
    double angleX = 0.0, angleY = 0.0, angleZ = 0.0;
    Quaternion curBest;
    double curBestEval = starCount*360.0;

    for (double i = 360.0; i > 0.01; i*=0.1)
    {
       FindPole(angleX,angleY,angleZ,i,i*0.1f,curBest,curBestEval);
    }
}

void Align::GoTo(Vector2 pos){
    pos = GetPolar(toMountQuat*GetCarthesian(pos));

    RaAxis.SlewTo(pos.x);
    DecAxis.SlewTo(pos.y);
}

void Align::Sync(Vector2 pos){
    realCoords.push_back(GetCarthesian(pos));
    measuredCoords.push_back(GetCarthesian(GetMountPos()));
    starCount++;
    if(starCount > 1){
        FindPole();
    }
}

void Align::ClearAlign(){
    measuredCoords.clear();
    realCoords.clear();
    starCount = 0;
    toMountQuat = Quaternion();
}

void Align::Update(double deltaTime){
    totalAngleOffset.x += rates.x*deltaTime;
    totalAngleOffset.y += rates.y*deltaTime;

    GoTo(GetMountPos()+totalAngleOffset);
}

void Align::SetConstantRate(Vector2 newRates){
    rates = newRates;
}

Vector2 Align::GetMountPos(){
    return Vector2(RaAxis.GetAngle(),DecAxis.GetAngle());
}
void Align::Guide(Vector2 dir){
    RaAxis.Guide(dir.x);
    DecAxis.Guide(dir.y);
}