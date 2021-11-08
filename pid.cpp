#include "pid.h"
#include "mbed.h"
#include "config.h"

class Pid_sys;

Pid_sys::Pid_sys()
{
    _Kp = 1;
    _Ki = 1;
    _Kd = 1;
    
    _integral=0;
    _derivative=0;
    _max_in = 1.0;
    _last_error = 0;
    _error = 0;
};

Pid_sys::Pid_sys(float p, float i, float d, float max_inte)
{
    _Kp = p;
    _Ki = i;
    _Kd = d;
    _max_in = max_inte;
}

float Pid_sys::get(float error)
{
    _integral += error;
    
    //range control
    if(_integral >= _max_in)
        _integral = _max_in;
    else if(_integral <= (-_max_in))
        _integral = -_max_in;
        
    _derivative = error - _last_error;
    _last_error = error;
    return _Kp*error + (1/_Ki)*_integral + _Kd*_derivative + 0.0;
}

void Pid_sys::set_pid(float p, float i, float d)
{
    _Kp = p;
    _Ki = i;
    _Kd = d;
}

void Pid_sys::set_max(float max_inte)
{
    _max_in = max_inte;
}