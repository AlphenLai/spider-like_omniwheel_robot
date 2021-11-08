#ifndef Servo_control_H_
#define Servo_control_H_

#include "mbed.h"

void set_servo_angle(uint8_t servo_no, float angle, uint32_t time, uint16_t steps=100, uint32_t offset=100);
void servo_control();
#endif