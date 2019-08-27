#include "common.h"

double sum[3] = {0, 0, 0};      // I制御のこれまでの積山量
double olddev[3] = {0, 0, 0};   // 目標値と現在の値の差分の前回値

double speed_test[3] = {0, 0, 0};   // PIDテスト用スピードパラメータ

void motor_pid(double speedref[3]){
    // PIDゲイン
    double Kp = 1.0;
    double Ki = 0.01;
    double Kd = 0.0;

    double en_speed[3] = {0, 0, 0};
    double input[3] = {0, 0, 0};

    for (int i = 0; i < 3;i++){
        // 単位換算
        en_speed[i] = delta_stock[i] * 2 * PI / 360 / SUMPLING_TIME_US * 1000000;

        double dev = speedref[i] - en_speed[i];
        sum[i] += (dev - olddev[i]) * SUMPLING_TIME_US / 2000000;
        double delta = (dev - olddev[i]) / SUMPLING_TIME_US / 1000000;

        input[i] = dev * Kp + sum[i] * Ki + delta * Kd;
        if(input[i]>1){
            input[i] = 1.0;
            printf("input over 1\n");
        }else if(input[i]<-1){
            input[i] = -1.0;
            printf("input under -1\n");
        }

        olddev[i] = dev;
    }

    motorspeed(input);
}