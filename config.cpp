#include "config.h"
#include "mbed.h"
#include "extended_servo.h"
#include "motor_control.h"
#include "QEI.h"
#include "serial.h"

Timer t;

bool ready_to_start = false;

RawSerial pc(USBTX, USBRX, 57600); // tx, rx
RawSerial nano(S1TX, PB_7, 57600);

Serial_buffer pc_serial;
Serial_buffer nano_serial;

//put in a struct next version
const char *VAR_TABLE[] = {
    "ready_to_start",
    "motor1",
    "motor2",
    "motor3",
    "motor4",
    "m1_speed",
    "m2_speed",
    "m3_speed",
    "m4_speed",
    "sys_v_x = 0",
    "sys_v_y = 0.5",
    "sys_v_theta = 0",
    "sys_x = 0",
    "sys_y = 0",
    "sys_theta = 0",
    "m1_encoder",
    "m2_encoder",
    "m3_encoder",
    "m4_encoder"
};

uint8_t var_table_len = sizeof(VAR_TABLE);
uint8_t var_table_ele = sizeof(VAR_TABLE[0]);

//hw var
float wheel_r = 0.019;
float chassis_R = 0.1453;
float motor1_pos = 45.0 * pi/180.0;
float motor2_pos = 315.0 * pi/180.0;
float motor3_pos = 225.0 * pi/180.0;
#if MOTOR_NUMBER == 4
float motor4_pos = 135.0 * pi/180.0;
#endif

//servo var
#if USE_SERVO1 == true
Servo servo1(SERVO1_PIN);
Extended_servo servo1_handler;
#endif

float servo1_init = 45.0;
float servo1_angle = servo1_init;
float servo1_angle_range = 90;
float servo1_max = 0.875;
float servo1_min = 0.47;

#if USE_SERVO2 == true
Servo servo2(SERVO2_PIN);
Extended_servo servo2_handler;
#endif

float servo2_init = 45;
float servo2_angle = servo2_init;
float servo2_angle_range = 90;
float servo2_max = 0.84;
float servo2_min = 0.415;

#if USE_SERVO3 == true
Servo servo3(SERVO3_PIN);
Extended_servo servo3_handler;
#endif

float servo3_init = 45;
float servo3_angle = servo3_init;
float servo3_angle_range = 90;
float servo3_max = 0.85;
float servo3_min = 0.445;

#if USE_SERVO4 == true
Servo servo4(SERVO4_PIN);
Extended_servo servo4_handler;
#endif

float servo4_init = 45;
float servo4_angle = servo4_init;
float servo4_angle_range = 90;
float servo4_max = 0.845;
float servo4_min = 0.44;
//---

//motor var
float max_speed = 0.25;
float min_speed = -1.0;
float sys_speed = 1.0;                  //speed of the whole system

PwmOut m1_pwm_out(MOTOR1_PWM_PIN);
PwmOut m2_pwm_out(MOTOR2_PWM_PIN);
PwmOut m3_pwm_out(MOTOR3_PWM_PIN);
#if MOTOR_NUMBER == 4
PwmOut m4_pwm_out(MOTOR4_PWM_PIN);
#endif

DigitalOut m1_in1_out(MOTOR1_IN1_PIN);
DigitalOut m1_in2_out(MOTOR1_IN2_PIN);
DigitalOut m2_in1_out(MOTOR2_IN1_PIN);
DigitalOut m2_in2_out(MOTOR2_IN2_PIN);
DigitalOut m3_in1_out(MOTOR3_IN1_PIN);
DigitalOut m3_in2_out(MOTOR3_IN2_PIN);
#if MOTOR_NUMBER == 4
DigitalOut m4_in1_out(MOTOR4_IN1_PIN);
DigitalOut m4_in2_out(MOTOR4_IN2_PIN);
#endif

float m1_speed;                         //speed of individual motor in rad/s
float m2_speed;                         //speed of individual motor in rad/s
float m3_speed;                         //speed of individual motor in rad/s
#if MOTOR_NUMBER == 4
float m4_speed;                         //speed of individual motor in rad/s
#endif
Motor_controller motor1(MOTOR1_HW_INV);
Motor_controller motor2(MOTOR2_HW_INV);
Motor_controller motor3(MOTOR3_HW_INV);
#if MOTOR_NUMBER == 4
Motor_controller motor4(MOTOR4_HW_INV);
#endif
//---

//system motion
float sys_v_x = 0;
float sys_v_y = 0;
float sys_v_theta = 5;

float sys_x = 0;
float sys_y = 0;
float sys_theta = 0;
//---

//encoder var
QEI m1_encoder(MOTOR1_ENC_A, MOTOR1_ENC_B, NC, 624);
QEI m2_encoder(MOTOR2_ENC_A, MOTOR2_ENC_B, NC, 624);
QEI m3_encoder(MOTOR3_ENC_A, MOTOR3_ENC_B, NC, 624);
#if MOTOR_NUMBER == 4
QEI m4_encoder(MOTOR4_ENC_A, MOTOR4_ENC_B, NC, 624);
#endif

float m1_enc = 0;
float m2_enc = 0;
float m3_enc = 0;
#if MOTOR_NUMBER == 4
float m4_enc = 0;
#endif

//enc angular velocity
float cyc_pulse = 440.0;

float enc_v_x = 0;
float enc_v_y = 0;
float enc_v_theta = 0;

//enc odom
float enc_x = 0;
float enc_y = 0;
float enc_theta = 0;
//---