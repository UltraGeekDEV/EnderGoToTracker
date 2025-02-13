#include <Arduino.h>
#include "./Align/Align.h"
#include "./DataHandler/DataHandler.h"
#include <RotaryEncoder.h>

HardwareSerial serial(USART1);

#define RAStep PC2
#define RADir PB9

#define DecStep PB8
#define DecDir PB7

uint32_t prevTime;
Axis Ra = Axis(AccelStepper(1,RAStep,RADir),96.0*51.0/11.0,16);
Axis Dec = Axis(AccelStepper(1,DecStep,DecDir),95,16);

Align mountModel(Ra,Dec);

DataHandler data(serial);

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

    if(data.command == ActionType::Sync){
      mountModel.Sync(vec);
    }else if(data.command == ActionType::GoTo){
      mountModel.GoTo(vec);
    } else if(data.command == ActionType::SetConstantRate){
      mountModel.SetConstantRate(vec);
    } else if(data.command == ActionType::Guide){
      mountModel.Guide(vec);
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

  mountModel.Update(deltaTime);

  if(data.CheckAndHandle()){
    HandleData();
  }
}

