#include "common.h"

class PID
{
    public:
        PID();
        double control(double target, double nowrpm);
        double PI_lateD(double target, double nowrpm);
        double control_P(double target, double nowrpm, double new_kp);
        double control_PI(double target, double nowrpm);
        void setParameter(double new_kp, double new_ki, double new_kd);
        void setParameter(double new_ku, double new_pu);
        void reset(double target);

        double ku;
        double pu;
        double kp;
        double ti;
        double td;
        double ki;
        double kd;

    private:
        double integral;
        double prev_hensa;
        double nowtime;
        double prev_time;
        double lateD;
};

void pid_controll(){
    
}

