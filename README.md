# ESP32-Robot

This project allows one to wirelessly control a four-wheeled mobile robot using the ESP32, an Arduino UNO and a computer. The ESP32 hosts an HTML webpage that accepts user commands from the keyboard. The keyboard requests are fulfilled using an asynchronous javascript framework for real time operation without webpage reloads. When a command is made using a keyboard, the ESP32 shares the command to the Arduino UNO through serial communication. The UNO actuates motors to each wheel based on the requested command.


![IMG_20210402_032455775 1](https://user-images.githubusercontent.com/77566595/113392549-51e5eb80-9363-11eb-865d-26e97041f173.jpg)


Click this link to see a video demo of the robot.
https://youtu.be/s_bXQFnLeg8
