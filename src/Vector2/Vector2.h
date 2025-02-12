#pragma once

class Vector2{
public:
    double x,y;
    Vector2(double _x, double _y):x(_x),y(_y){}
    Vector2():x(0),y(0){}
    Vector2 operator+(const Vector2& b);
};