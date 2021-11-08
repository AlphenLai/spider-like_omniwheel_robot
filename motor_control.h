#ifndef motor_control_H_
#define motor_control_H_
#include "mbed.h"
#include "config.h"

class Motor_controller
{
    private:
        signed char dir;
        float speed;
    public:
        Motor_controller(signed char wheel_inv);
        float get_speed();
        void set_speed(float spd);
        signed char get_dir();
        bool dir_ctr(uint8_t pin);
};

void motor_control();

#endif