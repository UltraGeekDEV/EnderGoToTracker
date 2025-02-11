#include <Arduino.h>
#include "./Axis/Axis.h"
#include "./DataHandler/DataHandler.h"
#include <RotaryEncoder.h>

HardwareSerial serial(USART1);

#define RAStep PC2
#define RADir PB9

#define DecStep PB8
#define DecDir PB7

uint32_t prevTime;
Axis Ra(AccelStepper(1,RAStep,RADir),96.0*51.0/11.0,16);
Axis Dec(AccelStepper(1,DecStep,DecDir),95,16);

DataHandler data(serial);

struct Vector2{
  double x,y;
};

void setup() {

  //Enable fan
  pinMode(PA0,OUTPUT);
  digitalWrite(PA0,HIGH);

  //Enable steppers
  pinMode(PC3,OUTPUT);
  digitalWrite(PC3,LOW);

  pinMode(PB2,INPUT_PULLUP);

  Ra.SetSlewRate(4000);
  Dec.SetSlewRate(4000);
  Ra.SetConstantRate(360.0/24/60/60);
  serial.begin(9600);
  serial.println("Hi");
  prevTime = micros();
}

void HandleData(){
  if(data.command == ActionType::Dither){

  }else{
    Vector2 vec;
    memcpy(&vec,data.buf,sizeof(Vector2));

    serial.println("Recieved:");
    serial.println(vec.x);
    serial.println(vec.y);

    if(data.command == ActionType::SetPosition){
      Ra.SetAngle(vec.x);
      Dec.SetAngle(vec.y);
    }else if(data.command == ActionType::MoveToPosition){
      Ra.SlewTo(vec.x);
      Dec.SlewTo(vec.y);
    } else if(data.command == ActionType::SetVelocity){
      Ra.SetConstantRate(vec.x);
      Dec.SetConstantRate(vec.y);
    } else if(data.command == ActionType::Guide){
      Ra.Guide(vec.x);
      Dec.Guide(vec.y);
    }
  }
}

void loop() {
  uint32_t curTime = micros();
  long delta = curTime-prevTime;

  if(delta < 0){
    delta = (1UL << 32) - prevTime + curTime;
  }

  prevTime = curTime;
  double deltaTime = (delta)/1000.0;

  Ra.Update(deltaTime);
  Dec.Update(deltaTime);

  if(data.CheckAndHandle()){
    HandleData();
  }
}

