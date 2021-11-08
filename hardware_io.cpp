#include "hardware_io.h"
#include "mbed.h"
#include "config.h"
#include "serial.h"
#include "QEI.h"
#include "servo_control.h"
#include "math_alg.h"
#include <math.h>
#include "motor_control.h"

extern bool ready_to_start;
extern Timer t;
extern RawSerial pc;

extern float servo1_angle;
extern float servo1_init;

extern float m1_speed;

#if USE_ADC_ROTARY == true
avg_filter adc_rotary;
#endif

extern Motor_controller motor1;

// Please notice that encoder uses pcio interrupt. Pin number should not duplicate
DigitalIn onboard_btn(ON_BRD_BTN);
//DigitalIn SW(ROTARY_PIN_SW);
//QEI rotary_input(ROTARY_PIN_A, ROTARY_PIN_B, NC, 624);
AnalogIn potentiometer1(ADC_PIN_1);

DigitalIn       btn(USER_BUTTON);

void hardware_io()
{
    while(ready_to_start == false)
    {
        if(onboard_btn == 0)    //on press
        {
            ready_to_start = true;
            pc.printf("ready to start\n\r");
        }
    }
    
    while(1)
    {
        wait(1);
        //motor1.set_speed(-motor1.get_speed());
        //printf("motor direction inverted");
        // non-stop rotary
        //rotary_input.getPulses()
        
        // adc rotary
        /*
        adc_rotary.fill_value(potentiometer1.read());
        float adc_rot_boundary = floor(((adc_rotary.get_value()-ADC_ROTARY_MIN)/(ADC_ROTARY_MAX - ADC_ROTARY_MIN))* 100) / 100;
        printf("\rwrite: %f, actual: %f\n\r", adc_rot_boundary, adc_rotary.get_value());
        m1_speed = adc_rot_boundary;
        */
        //set_servo_angle(1, 90.0-(adc_rot_boundary*90.0) ,0);
        //set_servo_angle(2, adc_rot_boundary*90.0 ,0);
        
    }
}