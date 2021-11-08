#include "servo_control.h"
#include "mbed.h"
#include "config.h"
#include "serial.h"
#include "Servo.h"
#include "extended_servo.h"

extern bool ready_to_start;
extern RawSerial pc;

#if USE_SERVO1 == true
extern Servo servo1;
#endif

extern float servo1_angle;
extern float servo1_angle_range;
extern float servo1_max;
extern float servo1_min;

#if USE_SERVO2 == true
extern Servo servo2;
#endif

extern float servo2_angle;
extern float servo2_angle_range;
extern float servo2_max;
extern float servo2_min;

#if USE_SERVO3 == true
extern Servo servo3;
#endif

extern float servo3_angle;
extern float servo3_angle_range;
extern float servo3_max;
extern float servo3_min;

#if USE_SERVO4 == true
extern Servo servo4;
#endif

extern float servo4_angle;
extern float servo4_angle_range;
extern float servo4_max;
extern float servo4_min;

extern Timer t;
//Ticker toggle_led_ticker;
//toggle_led_ticker.attach(&toggle_led, 0.1);

extern Extended_servo servo1_handler;
extern Extended_servo servo2_handler;
extern Extended_servo servo3_handler;
extern Extended_servo servo4_handler;

float last_servo1_angle = servo1_angle;
float last_servo2_angle = servo2_angle;
float last_servo3_angle = servo3_angle;
float last_servo4_angle = servo4_angle;

void set_servo_angle(uint8_t servo_no, float angle, uint32_t time, uint16_t steps, uint32_t offset)
{
    switch(servo_no)
    {
        case 1:
            #if USE_SERVO1 == true
            servo1_handler.reset(time, steps, offset);
            servo1_angle = angle;
            #endif
            break;
        case 2:
            #if USE_SERVO2 == true
            servo2_handler.reset(time, steps, offset);
            servo2_angle = angle;
            #endif
            break;
        case 3:
            #if USE_SERVO3 == true
            servo3_handler.reset(time, steps, offset);
            servo3_angle = angle;
            #endif
            break;
        case 4:
            #if USE_SERVO4 == true
            servo4_handler.reset(time, steps, offset);
            servo4_angle = angle;
            #endif
            break;
        default:
            break;
    }
}

void servo_control()
{    
    pc.printf("servo service starts\n\r");
    //initialize position
    #if USE_SERVO1 == true
    servo1.calibrate(0.00125, 180);
    servo1.write(servo1_angle/servo1_angle_range * (servo1_max-servo1_min) + servo1_min);
    servo1_handler.reset(0, 1);
    #endif
    
    #if USE_SERVO2 == true
    servo2.calibrate(0.00125, 180);
    servo2.write(servo2_angle/servo2_angle_range * (servo2_max-servo2_min) + servo2_min);
    servo2_handler.reset(0, 1);
    #endif
    
    #if USE_SERVO3 == true
    servo3.calibrate(0.00125, 180);
    servo3.write(servo3_angle/servo3_angle_range * (servo3_max-servo3_min) + servo3_min);
    servo3_handler.reset(0, 1);
    #endif
    
    #if USE_SERVO4 == true
    servo4.calibrate(0.00125, 180);
    servo4.write(servo4_angle/servo4_angle_range * (servo4_max-servo4_min) + servo4_min);
    servo4_handler.reset(0, 1);
    #endif
    
    wait(0.1);
    pc.printf("servo init done at %d\n\r", t.read_ms());
    while(ready_to_start == false)
        wait(0.01);
    
    pc.printf("servo loop starts at %d\n\r", t.read_ms());
    while(1)
    {
        if (servo1_angle != last_servo1_angle)
            servo1.write(servo1_angle/servo1_angle_range * abs(servo1_max-servo1_min) + servo1_min);
        //servo1_handler.servo_t(servo1, servo1_angle);
        
        if (servo2_angle != last_servo2_angle)
            servo2.write(servo2_angle/servo2_angle_range * abs(servo2_max-servo2_min) + servo2_min);
            
        if (servo3_angle != last_servo3_angle)
            servo3.write(servo3_angle/servo3_angle_range * abs(servo3_max-servo3_min) + servo3_min);
        if (servo4_angle != last_servo4_angle)
            servo4.write(servo4_angle/servo4_angle_range * abs(servo4_max-servo4_min) + servo4_min);
        //pc.printf("%f\t%f\t%f\t%f\n\r", servo1_angle, servo2_angle, servo3_angle, servo4_angle);
        
        last_servo1_angle = servo1_angle;
        last_servo2_angle = servo2_angle;
        last_servo3_angle = servo3_angle;
        last_servo4_angle = servo4_angle;
        wait(0.01);
    }
};