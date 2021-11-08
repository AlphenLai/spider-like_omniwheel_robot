#include "serial.h"
#include "mbed.h"
#include "config.h"
#include <string.h>

extern RawSerial pc;
extern RawSerial nano;
extern Serial_buffer pc_serial;
extern Serial_buffer nano_serial;


void Serial_buffer::reset_rx()
{
    memset(rx_buf, '\0', 50);
    memset(rx_rev, '\0', 50);
}
        
void pc_print(char* push)
{
    for(int i = 0; i<50; i++)
    {
        pc.putc(push[i]);
    }
    pc.putc('\n');
    pc.putc('\r');
}

void nano_print(char* push)
{
    for(int i = 0; i<50; i++)
    {
        pc.putc(push[i]);
    }
    pc.putc('\n');
    pc.putc('\r');
}

void cb_pc_ser()
{
    char c = pc.getc();
    //pc.putc(c);
    if (c == '\r')
    {
        for(int i = 0; i<50; i++)
        {
            pc_serial.rx_rev[i] = pc_serial.rx_buf[i];
            pc_serial.rx_buf[i] = '\0';
        }
        c = '\0';
        pc_print(pc_serial.rx_rev);
    }
    else if (c == '\n')
    {
        return;
    }
    else
    {
        strncat(pc_serial.rx_buf, &c, 1);
    }
}

void cb_nano_ser()
{
    char c = nano.getc();
    //pc.putc(c);
    if (c == '\r')
    {
        for(int i = 0; i<50; i++)
        {
            nano_serial.rx_rev[i] = nano_serial.rx_buf[i];
            nano_serial.rx_buf[i] = '\0';
        }
        c = '\0';
        //nano_print(nano_serial.rx_rev);
    }
    else if (c == '\n')
    {
        return;
    }
    else
    {
        strncat(nano_serial.rx_buf, &c, 1);
    }
}

void serial()
{
    pc.printf("serial service started\n\r");
    pc.attach(&cb_pc_ser);
    nano.attach(&cb_nano_ser);
    while(1)
        pc.putc(pc.getc());
}