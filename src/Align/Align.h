#pragma once
#include "../Axis/Axis.h"

class Align{
private:
    double ra;
    double dec;
    Axis RaAxis;
    Axis DecAxis;
public:
    void GoTo(double ra,double dec);
    void Sync(double ra,double dec);
    void ClearAlign();
};