#include "Align.h"

void Align::FindPole(float& x,float& y,float& z,float tileSize,float tileResolution){

}

void Align::GoTo(Vector2 pos){
    pos = GetPolar(toMountQuat*GetCarthesian(pos));

    RaAxis.SlewTo(pos.x);
    DecAxis.SlewTo(pos.y);
}

void Align::Sync(Vector2 pos){
    
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

    GoTo(Vector2(RaAxis.GetAngle()+totalAngleOffset.x,DecAxis.GetAngle()+totalAngleOffset.y));
}

void Align::SetConstantRate(Vector2 newRates){
    rates = newRates;
}