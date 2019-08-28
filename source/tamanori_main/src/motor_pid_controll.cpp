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

PID::PID()
{
    integral = 0;
    prev_hensa = 0;
    nowtime = 0;
    prev_time = 0;
    lateD = 0;
}

double PID::control(double target, double nowrpm)
{
    nowtime = ;
    double hensa = target - nowrpm;
    double dt = ;
    integral += (hensa + prev_hensa) / 2 * dt;
    double differential = (hensa - prev_hensa) / dt;
    double sousaryou = kp*hensa +ki*integral + kd*differential;
    prev_hensa = hensa;
    prev_time = ;
    return sousaryou;    
}

double PID::PI_lateD(double target, double nowrpm)
{
    nowtime = micros();
    double hensa = target - nowrpm;
    double dt = nowtime - prev_time;
    integral += (hensa + prev_hensa) / 2 * dt;
    double sousaryou = kp*hensa + ki*integral + kd*lateD;
    prev_hensa = hensa;
    prev_time = micros();
    lateD = (hensa - prev_hensa) / dt;
    return sousaryou;
}

double PID::control_P(double target, double nowrpm, double new_kp)
{
    double hensa = target - nowrpm;
    double sousaryou = new_kp*hensa;
    return sousaryou;
}

double PID::control_PI(double target, double nowrpm)
{
    kp = 0.45 * ku;
    ti = 0.83 * pu;
    ki = (1 / ti) * kp;
    nowtime = ;
    double hensa = target - nowrpm;
    double dt = nowtime - prev_time;
    integral += (hensa + prev_hensa) / 2 * dt;
    double sousaryou = kp*hensa + ki*integral;
    prev_hensa = hensa;
    prev_time = ;
    return sousaryou;
}
void PID::setParameter(double new_kp, double new_ki, double new_kd)
{  
  kp = new_kp;
  ki = new_ki;
  kd = new_kd;
}
void PID::setParameter(double new_ku, double new_pu)
{  
    ku = new_ku;
    pu = new_pu;
    
    kp = 0.60 * ku;
    ti = 0.50 * pu;
    td = 0.125 * pu;
    ki = (1 / ti) * kp;
    kd = td * kp;
}
void PID::reset(double target)
{
    integral    = 0;
    prev_hensa  = target;
    prev_time = ;
}

