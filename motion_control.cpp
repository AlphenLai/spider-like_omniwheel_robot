#include "motion_control.h"
#include "mbed.h"
#include "config.h"
#include "serial.h"
#include "pid.h"

extern bool ready_to_start;
extern RawSerial pc;
extern Serial_buffer pc_serial;

extern Timer t;
extern float motor1_pos;
extern float motor2_pos;
extern float motor3_pos;
#if MOTOR_NUMBER == 4
extern float motor4_pos;
#endif

//basically motor2_pos % (pi/2.0)
float motor1_pos_n = ((motor1_pos*(180/pi)) - int((motor1_pos*(180/pi))/90.0)*90)*(pi/180);
float motor2_pos_n = ((motor2_pos*(180/pi)) - int((motor2_pos*(180/pi))/90.0)*90)*(pi/180);
float motor3_pos_n = ((motor3_pos*(180/pi)) - int((motor3_pos*(180/pi))/90.0)*90)*(pi/180);
#if MOTOR_NUMBER == 4
float motor4_pos_n = ((motor4_pos*(180/pi)) - int((motor4_pos*(180/pi))/90.0)*90)*(pi/180);
#endif

extern float sys_v_theta;

float last_enc_x = 0;
float last_enc_y = 0;

extern float m1_enc;
extern float m2_enc;
extern float m3_enc;
#if MOTOR_NUMBER == 4
extern float m4_enc;
#endif

extern float enc_v_x;
extern float enc_v_y;
extern float enc_v_theta;

//enc odom
extern float enc_x;
extern float enc_y;
extern float enc_theta;



void motion_control()
{
    int32_t last_enc_t = 0;
    char buffer[50] = "motion control service starts\n\r";
    pc_print(buffer);
    //printf("motion control service starts\n\r");
    
    while(ready_to_start == false)
        wait(0.1);
    
    while(1)
    {
        //this is the overall accumulated displacement of the robot
        //use dt and record to find the complete path
        #if MOTOR_NUMBER == 3
        enc_x = m1_enc * cos(motor1_pos_n) - m2_enc * cos(motor2_pos_n) - m3_enc * sin(motor3_pos_n);
        enc_y = -m1_enc * sin(motor1_pos_n) - m2_enc * sin(motor2_pos_n) + m3_enc * cos(motor3_pos_n);
        #endif
        enc_v_theta = (enc_v_x==0 ? (pi/2) : atan(enc_v_y/enc_v_x));
        
        int32_t dt = t.read_ms() - last_enc_t;
        float this_enc_x = enc_x;
        float this_enc_y = enc_y;
        enc_v_x = (this_enc_x - last_enc_x) / (float)dt;
        enc_v_y = (this_enc_y - last_enc_y) / (float)dt;
        //record d(enc)/dt here, if there is enough ram
        
        last_enc_x = this_enc_x;
        last_enc_y = this_enc_y;
        last_enc_t = t.read_ms();
        //m4
        //printf("\renc- m1 : %d | m2: %d | m3 : %d | m4 : %d\n\r", m1_enc, m2_enc, m3_enc, m4_enc);
        //m3
        
        //sprintf(buffer, "enc- m1 : %f | m2: %f | m3 : %f", m1_enc, m2_enc, m3_enc);
        //sprintf(buffer, "enc- x : %f | y : %f | theta : %f", enc_v_x, enc_v_y, enc_v_theta);
        //pc_print(buffer);
    }
}