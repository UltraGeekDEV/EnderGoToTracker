#include "Align.h"

void Align::FindPole(float& x,float& y,float& z,float tileSize,float tileResolution){

}

void Align::GoTo(double ra,double dec){
    Vector2 position(ra,dec);

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
    totalAngleOffset.x += rates.x*deltaTime;
    totalAngleOffset.y += rates.y*deltaTime;
}

void Align::SetConstantRate(Vector2 newRates){
    rates = newRates;
}