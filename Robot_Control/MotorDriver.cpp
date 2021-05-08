#include "MotorDriver.h"

//Initialization Command
void MotorDriver::init(){

pinMode(PIN_Motor_PWMA, OUTPUT);
pinMode(PIN_Motor_PWMB, OUTPUT);
pinMode(PIN_Motor_AIN_1, OUTPUT);
pinMode(PIN_Motor_BIN_1, OUTPUT);
}

void MotorDriver::actuate(uint8_t spd){

  //Read a Command
  uint8_t command = "";
  command = Serial.read();

    switch (command){
        case 'F':
            digitalWrite(PIN_Motor_AIN_1, LOW);
            analogWrite(PIN_Motor_PWMA, spd);

            digitalWrite(PIN_Motor_BIN_1, HIGH);
            analogWrite(PIN_Motor_PWMB, spd);
            break;

        case 'B':
            digitalWrite(PIN_Motor_AIN_1, HIGH);
            analogWrite(PIN_Motor_PWMA, spd);

            digitalWrite(PIN_Motor_BIN_1, LOW);
            analogWrite(PIN_Motor_PWMB, spd);
            break;

        case 'L':
            digitalWrite(PIN_Motor_AIN_1, LOW);
            analogWrite(PIN_Motor_PWMA, spd);

            digitalWrite(PIN_Motor_BIN_1, LOW);
            analogWrite(PIN_Motor_PWMB, spd);
            break;

        case 'R':
            digitalWrite(PIN_Motor_AIN_1, HIGH);
            analogWrite(PIN_Motor_PWMA, spd);

            digitalWrite(PIN_Motor_BIN_1, HIGH);
            analogWrite(PIN_Motor_PWMB, spd);
            break;

        case 'O':
            analogWrite(PIN_Motor_PWMA, 0);
            analogWrite(PIN_Motor_PWMB, 0);
            break;
    }
}
