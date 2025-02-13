#include "./Vector2.h"

Vector2 Vector2::operator+(const Vector2& b){
    return Vector2(x+b.x,y+b.y);
}