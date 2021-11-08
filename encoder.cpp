#include "encoder.h"
#include "mbed.h"
#include "config.h"
#include "serial.h"
#include "QEI.h"

extern bool ready_to_start;
extern RawSerial pc;
extern Serial_buffer pc_serial;

extern QEI m1_encoder;
extern QEI m2_encoder;
extern QEI m3_encoder;
#if MOTOR_NUMBER == 4
extern QEI m4_encoder;
#endif

extern float m1_enc;
extern float m2_enc;
extern float m3_enc;
#if MOTOR_NUMBER == 4
extern float m4_enc;
#endif

extern float wheel_r;
extern float cyc_pulse;
float s_pulse = (2 * pi * wheel_r)/cyc_pulse;

void encoder()
{
    while(ready_to_start == false)
        wait(0.1);

    char buffer[50] = "encoder service starts\n\r";
    pc_print(buffer);
    //printf("encoder service starts\n\r");
    while(1)
    {        
        //converted to metres
        m1_enc = (float)m1_encoder.getPulses() * s_pulse;
        m2_enc = (float)m2_encoder.getPulses() * s_pulse;
        m3_enc = (float)m3_encoder.getPulses() * s_pulse;
        #if MOTOR_NUMBER == 4
        m4_enc = (float)m4_encoder.getPulses() * s_pulse;
        #endif
    }
}