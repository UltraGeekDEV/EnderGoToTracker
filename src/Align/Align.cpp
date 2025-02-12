#include "Align.h"
#include "../CPConvert.cpp"

void Align::FindPole(float& x,float& y,float& z,float tileSize,float tileResolution){

}

void Align::GoTo(double ra,double dec){
    Vector3 position(ra,dec,0);

    position = GetPolar(toMountQuat*GetCarthesian(position));

    RaAxis.SlewTo(position.x);
    DecAxis.SlewTo(position.y);
}

void Align::Sync(double ra,double dec){
    
}

void Align::ClearAlign(){
    measuredCoords.clear();
    realCoords.clear();
    starCount = 0;
    toMountQuat = Quaternion();
}

void Align::Update(double deltaTime){
    totalAngleOffset += raRate*deltaTime;
}

void Align::SetConstantRate(double rate){
    raRate = rate;
}