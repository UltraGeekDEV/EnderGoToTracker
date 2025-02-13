#include "Axis.h"

void Axis::SetSlewRate(double rate){
    slewRate = rate;
}
void Axis::SetAngle(double _angle){
    angle = _angle;
}

void Axis::SlewTo(double targetAngle){
    targetAngle = fmod(targetAngle,360);
    if(targetAngle < 0) targetAngle += 360;

    double rotation = targetAngle-angle;
    if(rotation > 180.0){
        rotation -= 360;
    } else if(rotation < -180){
        rotation += 360;
    }

    angle = targetAngle;

    double requiredMovement = rotation * microstepping * gearReduction / stepScale;

    targetStep += requiredMovement;
}

void Axis::GoToHome(){
    targetStep = 0;
}

void Axis::SetHome(){
    targetStep = 0;
}

void Axis::Update(){
    stepper.moveTo((long)targetStep);
    stepper.setMaxSpeed(slewRate);
    stepper.setSpeed(slewRate);
    stepper.runSpeedToPosition();
}

void Axis::Guide(double angle){
    targetStep += angle * microstepping * gearReduction / stepScale;
}

double Axis::GetAngle(){
    return angle;
}