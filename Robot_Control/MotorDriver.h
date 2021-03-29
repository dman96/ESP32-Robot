#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H
#include <arduino.h>

class MotorDriver
{
    public:
        void init();
        void actuate(uint8_t spd);

    private:
    //Assigned pins for direction and PWM
        #define PIN_Motor_PWMA 5
        #define PIN_Motor_PWMB 6
        #define PIN_Motor_BIN_1 7
        #define PIN_Motor_AIN_1 8
};


#endif // MOTORDRIVER_H
