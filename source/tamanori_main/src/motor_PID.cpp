#include "common.h"

double sum[3] = {0, 0, 0};      // I制御のこれまでの積山量
double olddev[3] = {0, 0, 0};   // 目標値と現在の値の差分の前回値
double en_speed[3] = {0, 0, 0}; // タイヤの実際の角速度[rad/s]
double speed_test[3] = {0, 0, 0};   // PIDテスト用スピードパラメータ

void motor_pid(double speedref[3]){
    // PIDゲイン
    double Kp = 0.08;
    double Ki = 0.2;
    double Kd = 0.004;

    double input[3] = {0, 0, 0};

    for (int i = 0; i < 3;i++){
        // ストールで負荷がかかりすぎないため処理
        double speedref_ = speedref[i];
        if(-4.0<speedref[i] && speedref[i]<4.0){
            speedref_ = 0.0;
        }

        // 単位換算
        en_speed[i] = delta_stock[i] * 2 * PI / 360 / SUMPLING_TIME_US * 1000000*2/5;

        double dev = speedref_ - en_speed[i];
        sum[i] += ((dev - olddev[i]) * SUMPLING_TIME_US / 2000000);
        double delta = (dev - olddev[i]) / SUMPLING_TIME_US * 1000000;

        input[i] += (dev * Kp + sum[i] * Ki + delta * Kd);
        
        if(input[i]>1){
            input[i] = 1.0;
            //pc.printf("input over : %.1f\n",input[i]);
        }else if(input[i]<-1){
            input[i] = -1.0;
            //pc.printf("input under : %.1f\n",input[i]);
        }

        olddev[i] = dev;

        // ストールで負荷がかかりすぎないため処理
        if(-0.2<input[i] && input[i]<0.2){
            input[i] = 0.0;
        }
    }

    motorspeed(input);
}