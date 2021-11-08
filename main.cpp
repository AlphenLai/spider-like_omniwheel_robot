#include "mbed.h"
#include "config.h"
#include "serial.h"
#include "servo_control.h"
#include "hardware_io.h"
#include "motor_control.h"
#include "encoder.h"
#include "motion_control.h"
#include "usb_interface.h"
#include "controller.h"

#define USE_CONSOLE true

//place this line to io thread cpp later
DigitalOut debug_led(LD2);
extern Timer t;
extern RawSerial pc;

extern float sys_v_x;
extern float sys_v_y;
extern float sys_v_theta;

void led_thread()
{
    while (true) {
        debug_led = !debug_led;
        wait(1);
    }
}

int main()
{
    //Thread thread1(osPriorityNormal, 0.5 * 1024);   //0.5 * 1k stacks
    Thread thread2(osPriorityNormal, 1 * 1024);
    Thread thread3(osPriorityNormal, 0.5 * 1024);
    Thread thread4(osPriorityNormal, 1 * 1024);
    //Thread thread5(osPriorityNormal, 0.5 * 1024);
    //Thread thread6(osPriorityNormal, 1 * 1024);
    //Thread thread7(osPriorityNormal, 1 * 1024);
    Thread thread8(osPriorityNormal, 1 * 1024);
    Thread thread9(osPriorityNormal, 0.5 * 1024);
    
    pc.printf("\n\n=== Omniwheel Robot Test Platform ===\n\r");
    pc.printf("                            --Unit 00 v0 mod 1\n\n\r");
    t.start();
    
    //thread1.start(led_thread);
    thread2.start(servo_control);
    thread3.start(hardware_io);    
    thread4.start(motor_control);
    //thread5.start(encoder);
    //thread6.start(motion_control);
    //thread7.start(usb_interface);
    thread8.start(controller);
    thread9.start(serial);
    
    while(1)
    {
        wait(30);
        char buffer[50] = "running\n\r";
        pc_print(buffer);
        
        /*
        sys_v_x = 0.0;
        sys_v_y = 0.0;
        sys_v_theta = 3.0;
        wait(1);
        */
    }
}
