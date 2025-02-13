#pragma once

#include <Arduino.h>
#include <AccelStepper.h>

class Axis{

private:
AccelStepper stepper;
double slewRate = 2000;
double constantRate = 0;
double gearReduction;
double angle = 0;
double stepScale = 1.8;
double targetStep = 0;
int microstepping;

public:
    void SetSlewRate(double rate);
    void SetAngle(double angle);
    void SlewTo(double angle);
    void Update();
    void GoToHome();
    void SetHome();
    void Guide(double angle);
    double GetAngle();
    Axis(AccelStepper _stepper,double _gearReduction,int _microstepping):stepper(_stepper),gearReduction(_gearReduction),microstepping(_microstepping){}
};