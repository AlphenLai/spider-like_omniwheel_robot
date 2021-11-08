#include "math_alg.h"
#include "mbed.h"

avg_filter::avg_filter()
{
    float temp_arr[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    memcpy(array, temp_arr, sizeof(float));
    sum = 0;
    average = 0;
    zero = 0;
    cycle = 0;
}

//note that this exclude all 0
void avg_filter::fill_value(float infill)
{
    array[cycle] = infill;
    zero = 0;
    sum = 0;
    uint8_t elements = sizeof(array)/sizeof(array[0]);
    for (int i = 0; i<elements; i++)
    {
        if (array[i] == 0)
            zero++;
        sum += array[i];
    }
    average = sum/(elements-zero);
    cycle++;
    if(cycle > elements)
        cycle = 0;
}

float avg_filter::get_value()
{
    return average;
}

float boundary(float min, float input, float max)
{
    if(input < min)
        return min;
    else if (input > max)
        return max;
    else
        return input;
}

float scaling(float min, float input, float max)
{
    if(input < min)
        return 0.0;
    else if (input > max)
        return 1.0;
    else
        return (input-min)/(max-min);
}