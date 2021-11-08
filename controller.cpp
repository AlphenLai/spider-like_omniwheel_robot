#include "controller.h"
#include "mbed.h"
#include "config.h"
#include "serial.h"
#include <vector>
#include <string>
#include "stdio.h"

extern RawSerial pc;
extern RawSerial nano;
extern Serial_buffer pc_serial;
extern Serial_buffer nano_serial;

extern bool ready_to_start;
extern float sys_v_x;
extern float sys_v_y;
extern float sys_v_theta;

extern float servo1_angle;
extern float servo2_angle;
extern float servo3_angle;
extern float servo4_angle;

extern float motor1_pos;
extern float motor2_pos;
extern float motor3_pos;
extern float motor4_pos;

uint16_t ctr_UP = 0;
uint16_t ctr_DOWN = 0;

void controller()
{
    char buffer[50] = "controller service starts\n\r";
    pc_print(buffer);
    
    float joystick[4] = {0.0, 0.0, 0.0, 0.0};
    float analog_but[2] = {0.0, 0.0};
    uint16_t buttons = 0;
    
    char CT[50];
    
    while(1)
    {
        //pc_print(nano_serial.rx_rev);        
        char * p;
        char *input[7];
        int i = 0;
        
        memset(input, '\0', sizeof(input));
        memcpy(CT, nano_serial.rx_rev, 50);
        strtok(CT, "\n");
        p = strtok (CT, " ");
        while (p != NULL)
        {
            input[i++] = p;
            p = strtok (NULL, " ");
        }
        /*
        for (int i = 0; i<7; i--)
        {
            memset(buffer, '\0', sizeof(buffer));
            sprintf(buffer, "ct[%d]=[%s]", i, input[i]);
            pc_print(buffer);
        }
        */
        if(input[0])
        {
            joystick[0] = atof(input[0]);
            joystick[1] = atof(input[1]);
            joystick[2] = atof(input[2]);
            joystick[3] = atof(input[3]);
            analog_but[0] = atof(input[4]);
            analog_but[1] = atof(input[5]);
            buttons = atoi(input[6]);
            
            /*
            memset(buffer, '\0', sizeof(buffer));
            //sprintf(buffer, "arr[%d]=[%f]", 0, atof(input[6]));
            sprintf(buffer, "buttons=[%d]", buttons);
            pc_print(buffer);
            */
        }
        //LB/RB/L3/R3/UP/DOWN/LEFT/RIGHT/A/B/X/Y/VIEW/MENU/XBOX
        if ((buttons&0b0000000000000010))
            ready_to_start = 1;
        
        //for some reason spider setup
        //effective only when ready
        if (ready_to_start == 1)
        {            
            sys_v_x = -joystick[0];
            sys_v_y = -joystick[1];
            sys_v_theta = -joystick[2]*10.0;
            
            if ((buttons&0b000100000000000))        //to y axis (up)
            {
                ctr_UP++;
                if (ctr_UP >= 3)
                {
                    servo1_angle < 90.0 ? servo1_angle += 1.0 : servo1_angle = 90.0;
                    servo2_angle > 0.0 ? servo2_angle -= 1.0 : servo2_angle = 0.0;
                    servo3_angle < 90.0 ? servo3_angle += 1.0 : servo3_angle = 90.0;
                    servo4_angle > 0.0 ? servo4_angle -= 1.0 : servo4_angle = 0.0;
                    motor1_pos > (0.0 * pi/180.0) ? motor1_pos -= (1.0 * pi/180.0) : motor1_pos = (0.0 * pi/180.0);
                    motor2_pos < (180.0 * pi/180.0) ? motor2_pos += (1.0 * pi/180.0) : motor2_pos = (180.0 * pi/180.0);
                    motor3_pos > (180.0 * pi/180.0) ? motor3_pos -= (1.0 * pi/180.0) : motor3_pos = (180.0 * pi/180.0);
                    motor4_pos < (360.0 * pi/180.0) ? motor4_pos += (1.0 * pi/180.0) : motor4_pos = (360.0 * pi/180.0);
                    
                    char buffer[50] = "approach to y:1deg\n\r";
                    pc_print(buffer);
                    ctr_UP = 0;
                }
            }
            else if ((buttons&0b000010000000000))   //to x axis (down)
            {
                ctr_DOWN++;
                if (ctr_DOWN >= 3)
                {
                    servo1_angle > 0.0 ? servo1_angle -= 1 : servo1_angle = 0.0;
                    servo2_angle < 90.0 ? servo2_angle += 1 : servo2_angle = 90.0;
                    servo3_angle > 0.0 ? servo3_angle -= 1 : servo3_angle = 0.0;
                    servo4_angle < 90.0 ? servo4_angle += 1 : servo4_angle = 90.0;
                    motor1_pos < (90.0 * pi/180.0) ? motor1_pos += (1.0 * pi/180.0) : motor1_pos = (90.0 * pi/180.0);
                    motor2_pos > (90.0 * pi/180.0) ? motor2_pos -= (1.0 * pi/180.0) : motor2_pos = (90.0 * pi/180.0);
                    motor3_pos < (270.0 * pi/180.0) ? motor3_pos += (1.0 * pi/180.0) : motor3_pos = (270.0 * pi/180.0);
                    motor4_pos > (270.0 * pi/180.0) ? motor4_pos -= (1.0 * pi/180.0) : motor4_pos = (270.0 * pi/180.0);
                    
                    char buffer[50] = "approach to x:1deg\n\r";
                    pc_print(buffer);
                    ctr_DOWN = 0;
                }
            }
        }
    }
}