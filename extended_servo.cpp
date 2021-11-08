#include "extended_servo.h"
#include "mbed.h"
#include "Servo.h"
#include "config.h"

class Extended_servo;

extern float servo1_angle_range;
extern float servo1_max;
extern float servo1_min;

extern Timer t;

void Extended_servo::reset(uint32_t action_duration_ms, uint16_t step_size, uint32_t delay_offset)
{
    steps = step_size;
    duration_t = action_duration_ms;
    last_entry_t = 0;
    servo_step_delay_constant = delay_offset;
}

void Extended_servo::servo_t(Servo &servo_obj, float destination_angle)
{
    if (steps > 0)
    {
        // printf has the best effect on smoothness, but it will spam the uart channel. 
        // 0.005 is alright but please feel free to try.
        //printf("\rservo_running\n\r");
        wait(0.005);
        
        int32_t step_t = duration_t / steps;
        if (t.read_ms() - last_entry_t + servo_step_delay_constant> step_t)
        {
            servo_step_delay_constant = t.read_ms() - last_entry_t - step_t;
            float destination_percentage = destination_angle/servo1_angle_range * (servo1_max-servo1_min) + servo1_min;
            float curr_percentage = servo_obj.read();
            float percentage_per_step = (destination_percentage - curr_percentage)/steps;
            servo_obj.write(curr_percentage + percentage_per_step);
            steps--;
            duration_t -= step_t;
            last_entry_t = t.read_ms();
            // servo motion ends
            if (steps == 0)
                printf("servo has arrived to its destination at %d\n\r", t.read_ms());
        }
    }
}