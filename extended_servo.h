#ifndef Extended_servo_H_
#define Extended_servo_H_

#include "Servo.h"

class Extended_servo
{
    public:
        uint16_t steps;
        int32_t duration_t;
        int32_t last_entry_t;
        int32_t servo_step_delay_constant;
        
        void reset(uint32_t action_duration_ms=3000, uint16_t step_size=100, uint32_t delay_offset=100);
        void servo_t(Servo &servo_obj, float destination_angle);
};

void extended_servo();

#endif