/*
********************************** 
Created by Dave Mandyam
**********************************

This code and the associated library operate the motors based on the serial commands from the ESP32. For this project, the DRV8835 motor driver was used. One may need to adjust the pins in the MotorDriver.h file if a different motor driver is used.
The code accepts four commands from the ESP32: "F", "B", "L", "R" and "O". Listed below are the movement directions. Depending on the command, the robot moves in that direction.

F - Forward
B - Backward
L - Left
R - Right
O - Stop

If you have any questions, please contact me at davem1996@gmail.com
*/


#include "MotorDriver.h"
#include <arduino.h>

//Creating a MotorDriver Object
MotorDriver Command;


//Desired Motor Speed (Maximum is 255)
uint8_t spd = 100;


void setup() {
  Serial.begin(9600);
  
  //Initialize the Motors
  Command.init();

}

void loop() {
  //Read a Command
  if (Serial.available()>0){
    //Actuate the Motors
    Command.actuate(spd);
  }

 delay(50);

}
