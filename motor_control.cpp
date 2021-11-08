#include "motor_control.h"
#include "mbed.h"
#include "config.h"
#include "serial.h"
#include "math_alg.h"
#include "pid.h"

extern bool ready_to_start;
extern RawSerial pc;
extern Serial_buffer pc_serial;

extern float wheel_r;
extern float chassis_R;

extern float motor1_pos;
extern float motor2_pos;
extern float motor3_pos;
#if MOTOR_NUMBER == 4
extern float motor4_pos;
#endif

extern float max_speed;
extern float min_speed;
extern float sys_speed;

extern Motor_controller motor1;
extern Motor_controller motor2;
extern Motor_controller motor3;
#if MOTOR_NUMBER == 4
extern Motor_controller motor4;
#endif

extern PwmOut m1_pwm_out;
extern PwmOut m2_pwm_out;
extern PwmOut m3_pwm_out;
#if MOTOR_NUMBER == 4
extern PwmOut m4_pwm_out;
#endif

extern DigitalOut m1_in1_out;
extern DigitalOut m1_in2_out;
extern DigitalOut m2_in1_out;
extern DigitalOut m2_in2_out;
extern DigitalOut m3_in1_out;
extern DigitalOut m3_in2_out;
#if MOTOR_NUMBER == 4
extern DigitalOut m4_in1_out;
extern DigitalOut m4_in2_out;
#endif

extern float m1_speed;
extern float m2_speed;
extern float m3_speed;
#if MOTOR_NUMBER == 4
extern float m4_speed;
#endif

extern float sys_v_x;
extern float sys_v_y;
extern float sys_v_theta;

extern float sys_x;
extern float sys_y;
extern float sys_theta;
float max_rad = (chassis_R/wheel_r)*10;   //max possible angular speed of a wheel, assume sys_v_theta = 1 is maximum

Pid_sys enc_theta_offset(1, 1, 1, 0.05);
extern float enc_v_theta;

Motor_controller::Motor_controller(signed char wheel_inv)
{
    dir = wheel_inv;
    speed = 1.0;    //start up speed
}

float Motor_controller::get_speed()
{
    return speed;
}

void Motor_controller::set_speed(float spd)
{
    speed = dir * spd;
}

signed char Motor_controller::get_dir()
{
    return dir;     //whether the wheel is inverted
}
        
bool Motor_controller::dir_ctr(uint8_t pin)
{
    if (speed >= 0)          //+ve, 01
    {
        if (pin == 1)
            return 0;
        else if (pin == 2)
            return 1;
    } 
    else if (speed < 0)      //-ve, 10
    {
        if (pin == 1)
            return 1;
        else if (pin == 2)
            return 0;
    }
    return 0;
}

void motor_control()
{
    while(ready_to_start == false)
        wait(0.1);

    char buffer[50] = "motor service starts\n\r";
    pc_print(buffer);
    //printf("motor service starts\n\r");
    
    //m1_pwm_out.period_ms(MOTOR_PWM_PERIOD_MS);
    while(1)
    {
        //angle correction
        //float ref_offset = enc_theta_offset.get( (sys_v_theta - enc_v_theta)/enc_v_theta);
        //printf("\rsys_v : %f enc_v: %f dtheta: %f\n\r", sys_v_theta, enc_v_theta, ref_offset);
        
        #if MOTOR_NUMBER == 3
        //float temp0 = boundary(min_speed, motor4.get_speed(), max_speed);
        //printf("\rpwm4 out = %f\n", temp0);
        m1_speed = (-sin(sys_theta + motor1_pos) * cos(sys_theta) * sys_v_x + cos(sys_theta + motor1_pos) * cos(sys_theta) * sys_v_y + chassis_R * (sys_v_theta/*+ ref_offset*/))/wheel_r;
        motor1.set_speed(m1_speed/max_rad);
        m1_in1_out = motor1.dir_ctr(1);
        m1_in2_out = motor1.dir_ctr(2);
        //m1_pwm_out.write(boundary(min_speed, abs(motor1.get_speed()), max_speed));
        m1_pwm_out.write(abs(motor1.get_speed()));
        
        m2_speed = (-sin(sys_theta + motor2_pos) * cos(sys_theta) * sys_v_x + cos(sys_theta + motor2_pos) * cos(sys_theta) * sys_v_y + chassis_R * (sys_v_theta/* + ref_offset*/))/wheel_r;
        motor2.set_speed(m2_speed/max_rad);
        m2_in1_out = motor2.dir_ctr(1);
        m2_in2_out = motor2.dir_ctr(2);
        m2_pwm_out.write(abs(motor2.get_speed()));
        
        m3_speed = (-sin(sys_theta + motor3_pos) * cos(sys_theta) * sys_v_x + cos(sys_theta + motor3_pos) * cos(sys_theta) * sys_v_y + chassis_R * (sys_v_theta/* + ref_offset*/))/wheel_r;
        motor3.set_speed(m3_speed/max_rad);
        m3_in1_out = motor3.dir_ctr(1);
        m3_in2_out = motor3.dir_ctr(2);
        m3_pwm_out.write(abs(motor3.get_speed()));
        #endif
        
        #if MOTOR_NUMBER == 4
        //placeholder
        m1_speed = (-sin(sys_theta + motor1_pos) * cos(sys_theta) * sys_v_x + cos(sys_theta + motor1_pos) * cos(sys_theta) * sys_v_y + chassis_R * (sys_v_theta/*+ ref_offset*/))/wheel_r;
        motor1.set_speed(m1_speed/max_rad);
        m1_in1_out = motor1.dir_ctr(1);
        m1_in2_out = motor1.dir_ctr(2);
        m1_pwm_out.write(abs(motor1.get_speed()));
        
        m2_speed = (-sin(sys_theta + motor2_pos) * cos(sys_theta) * sys_v_x + cos(sys_theta + motor2_pos) * cos(sys_theta) * sys_v_y + chassis_R * (sys_v_theta/* + ref_offset*/))/wheel_r;
        motor2.set_speed(m2_speed/max_rad);
        m2_in1_out = motor2.dir_ctr(1);
        m2_in2_out = motor2.dir_ctr(2);
        m2_pwm_out.write(abs(motor2.get_speed()));
        
        m3_speed = (-sin(sys_theta + motor3_pos) * cos(sys_theta) * sys_v_x + cos(sys_theta + motor3_pos) * cos(sys_theta) * sys_v_y + chassis_R * (sys_v_theta/* + ref_offset*/))/wheel_r;
        motor3.set_speed(m3_speed/max_rad);
        m3_in1_out = motor3.dir_ctr(1);
        m3_in2_out = motor3.dir_ctr(2);
        m3_pwm_out.write(abs(motor3.get_speed()));
        
        m4_speed = (-sin(sys_theta + motor4_pos) * cos(sys_theta) * sys_v_x + cos(sys_theta + motor4_pos) * cos(sys_theta) * sys_v_y + chassis_R * (sys_v_theta/* + ref_offset*/))/wheel_r;
        motor4.set_speed(m4_speed/max_rad);
        m4_in1_out = motor4.dir_ctr(1);
        m4_in2_out = motor4.dir_ctr(2);
        m4_pwm_out.write(abs(motor4.get_speed()));
        #endif
        
        //printf("\rout- m1 : %.3f | m2: %.3f | m3 : %.3f\n\r", motor1.get_speed(), motor2.get_speed(), motor3.get_speed());
        //printf("\r%.3f | %.3f | %.3f | %.3f\n\r", motor1.get_speed(), motor2.get_speed(), motor3.get_speed(), motor4.get_speed());
        while(ready_to_start == false)
        {
            m1_pwm_out.write(0.0);
            m2_pwm_out.write(0.0);
            m3_pwm_out.write(0.0);
            #if MOTOR_NUMBER == 4
            m4_pwm_out.write(0.0);
            #endif
            wait(0.1);
        }
    }
}