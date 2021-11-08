#include "usb_interface.h"
#include "mbed.h"
#include "config.h"
#include "serial.h"
#include <string.h>

extern RawSerial pc;
extern Serial_buffer pc_serial;

static const char *CMD_TABLE[] = {
    "RDY", "MOV", "SPD", "POS", "TEST", "MT", "SET", "GET"
};

extern const char *VAR_TABLE[];

extern uint8_t var_table_len;
extern uint8_t var_table_ele;

//var list start here
extern bool ready_to_start;
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
extern uint32_t m1_enc;
extern uint32_t m2_enc;
extern uint32_t m3_enc;
#if MOTOR_NUMBER == 4
extern uint32_t m4_enc;
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


int table_lookup(char const ** table, uint8_t table_length, char * target)
{
    for (uint8_t i = 0; i < table_length; i++)
    {
        if (strcmp(target, table[i]) == 0)
            return i;
    }
    return -1;
}

void proc_cmd(char raw[])
{    
    char buffer[50];
    /*
    if (strcmp("RDY 1", raw) == 0)
    {
        strncpy(buffer, "yes", 50);
        pc_print(buffer);
    }
    
    for(int i = 0; i <50; i++)
    {
        memset(buffer, '\0', sizeof(buffer));
        sprintf(buffer, "raw[%d] = [%c]", i, raw[i]);
        pc_print(buffer);
    }
    */
    
    char * p;
    char *array[10];
    int i = 0;
    
    memset(array, '\0', sizeof(array));
    
    p = strtok (raw, " ");
    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, " ");
    }
    
    wait(0.1);
    if(array[0])
    {
        switch(table_lookup(CMD_TABLE, (sizeof(CMD_TABLE)/sizeof(CMD_TABLE[0])), array[0]))
        {
            //change CMD_TABLE as well, if you want to change the case numbers
            case 0:
                {
                    //strncpy(buffer, "yes array", 50);
                    sprintf(buffer, "ready_to_start = %d", atoi(array[1]));
                    pc_print(buffer);
                    ready_to_start = atoi(array[1]);
                    pc_serial.reset_rx();
                }
                break;
            case 1:
                {
                    pc.printf("MOV ");
                    if (strcmp(array[1], "SPD") == 0)
                    {
                        pc.printf("SET SPD x: %f y: %f, theta: %f\n\r", atof(array[2]), atof(array[3]), atof(array[4]));
                        sys_v_x = atof(array[2]);
                        sys_v_y = atof(array[3]);
                        sys_v_theta = atof(array[4]);
                        pc_serial.reset_rx();
                    }
                    else if (strcmp(array[1], "POS") == 0)
                    {
                        pc.printf("SET POS x: %f y: %f, theta: %f\n\r", atof(array[2]), atof(array[3]), atof(array[4]));
                        pc.printf("function not opened yet\n\r");
                        pc_serial.reset_rx();
                    }
                    else
                        pc.printf("\n\rError: 2nd argu invalid\n\r");
                }
                break;
            case 4:
                {
                    pc.printf("TEST ");
                    if (strcmp(array[1], "MT") == 0)
                    {
                        pc.printf("MT %d speed: %f\n\r", atoi(array[2]), atof(array[3]));
                        switch(atoi(array[2]))
                        {
                            case 1:
                                {
                                    m1_in1_out = 1;
                                    m1_in2_out = 0;
                                    m1_pwm_out.write(atof(array[3]));
                                }
                                break;
                            case 2:
                                {
                                    m2_in1_out = 1;
                                    m2_in2_out = 0;
                                    m2_pwm_out.write(atof(array[3]));
                                }
                                break;
                            case 3:
                                {
                                    m3_in1_out = 1;
                                    m3_in2_out = 0;
                                    m3_pwm_out.write(atof(array[3]));
                                }
                                break;
                            #if MOTOR_NUMBER == 4
                            case 4:
                                {
                                    m4_in1_out = 1;
                                    m4_in2_out = 0;
                                    m4_pwm_out.write(atof(array[3]));
                                }
                                break;
                            #endif
                            default:
                                pc.printf("\n\rError: 2nd argu invalid\n\r");
                                break;
                        }
                    }
                    pc_serial.reset_rx();
                }
                break;
            case 6:
                {
                    pc.printf("function not opened yet\n\r");
                    pc.printf("SET ");
                    switch(table_lookup(VAR_TABLE, var_table_len / var_table_ele, array[1]))
                    {
                        case 0:
                            pc.printf("%s %f\n\r", VAR_TABLE[0], atof(array[2]));
                            break;
                        case 1:
                            pc.printf("%s %f\n\r", VAR_TABLE[1], atof(array[2]));
                            break;
                        case 2:
                            pc.printf("%s %f\n\r", VAR_TABLE[2], atof(array[2]));
                            break;
                        case 3:
                            pc.printf("%s %f\n\r", VAR_TABLE[3], atof(array[2]));
                            break;
                        default:
                            pc.printf("\n\rError: 2nd argu invalid\n\r");
                            break;
                    }
                }
                break;
            case 7:
                {
                    pc.printf("GET ");
                    switch(table_lookup(VAR_TABLE, var_table_len / var_table_ele, array[1]))
                    {
                        case 15:
                            pc.printf("%s: %d\n\r", VAR_TABLE[15], m1_enc);
                            break;
                        case 16:
                            pc.printf("%s: %d\n\r", VAR_TABLE[16], m2_enc);
                            break;
                        case 17:
                            pc.printf("%s: %d\n\r", VAR_TABLE[17], m3_enc);
                            break;
                        #if MOTOR_NUMBER == 4
                        case 18:
                            pc.printf("%s: %d\n\r", VAR_TABLE[18], m4_enc);
                            break;
                        #endif
                        default:
                            pc.printf("\n\rError: 2nd argu invalid\n\r"); 
                            break;
                    }
                }
                break;
            default:
                {
                    pc_serial.reset_rx();
                    strncpy(buffer, "Error: 1st argu invalid", 50);
                    pc_print(buffer);
                } 
                break;
        }
    }
}

void usb_interface()
{
    char buffer[50] = "usb_interface ready\n\r";
    pc_print(buffer);
    //pc.printf("usb_interface ready");
    while(1)
    {
        /*
        strncpy(buffer, "rx_buf:", 50);
        pc_print(buffer);
        pc_print(pc_serial.rx_buf);
        */
        /*
        strncpy(buffer, "rx_rev (sent to proc):", 50);
        pc_print(buffer);
        pc_print(pc_serial.rx_rev);
        */
        proc_cmd(pc_serial.rx_rev);
    }
}