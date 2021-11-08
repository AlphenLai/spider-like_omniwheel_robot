#ifndef Math_alg_H_
#define Math_alg_H_

#include "mbed.h"

class avg_filter
{
    private:
        float array[20];
        float sum;
        float average;
        uint16_t zero;
        uint16_t cycle;
    
    public:
        avg_filter();
        void fill_value(float infill);
        float get_value();
};

float boundary(float min, float input, float max);
float scaling(float min, float input, float max);

#endif