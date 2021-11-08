#ifndef USB_INTERFACE_H_
#define USB_INTERFACE_H_
#include "mbed.h"

int table_lookup(char const ** table, uint8_t table_length, char * target);
void proc_cmd(char * cmd);
void onCharReceived();
void get_cmd();
void usb_interface();

#endif

