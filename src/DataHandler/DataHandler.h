#pragma once

#include <Arduino.h>

enum class ActionType : uint8_t
{
    SetVelocity,
    SetPosition,
    MoveToPosition,
    Dither,
    Guide
};

class DataHandler{
private:
HardwareSerial& serial;
public:
ActionType command = ActionType::SetVelocity;
bool doneReading = false;
uint8_t buf_len = 0;
uint8_t cur_byte = 0;
uint8_t* buf = nullptr;
bool CheckAndHandle();
DataHandler(HardwareSerial& _serial):serial(_serial){}
};