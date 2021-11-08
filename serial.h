#ifndef Serial_H_
#define Serial_H_

class Serial_buffer
{
    public:
        char rx_buf[50];
        char rx_rev[50];
        void reset_rx();
};

void pc_print(char* push);
void nano_print(char* push);
void cb_pc_ser();
void cb_nano_ser();
void serial();
#endif