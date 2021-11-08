#ifndef Pid_H_
#define Pid_H_

class Pid_sys
{
    public:
        Pid_sys();
        Pid_sys(float p, float i, float d, float max_inte);

        float get(float error);
        void set_pid(float p, float i, float d);
        void set_max(float max_inte);
    private:
        float _Kp;
        float _Ki;
        float _Kd;
        
        float _integral;
        float _derivative;
        float _max_in;
        float _last_error;
        float _error;
};

#endif