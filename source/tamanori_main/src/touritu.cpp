#include "common.h"
#define WHEEL_RADIUS 30.0 //[mm]

double omegavec[3] = {0, 0, 0};   //各速度ベクトル
double wheelpos0[3] = {0, 90.93, 85.77};   //接点位置ベクトル0
double wheelpos1[3] = {78.75, -45.47, 85.77};   //接点位置ベクトル1
double wheelpos2[3] = {-78.75, -45.47, 85.77};   //接点位置ベクトル2
double wheeldrive0[3] = {1, 0, 0};   //駆動ベクトル0
double wheeldrive1[3] = {-0.5, -sqrt(3)/2, 0};   //駆動ベクトル1
double wheeldrive2[3] = {-0.5, sqrt(3)/2, 0};   //駆動ベクトル2
double wheelspeed[3] = {0, 0, 0};   //車輪外周速さ

void matrix_product(double in1[3], double in2[3], double out[3]){
    out[0] = in1[1] * in2[2] - in1[2] * in2[1];
    out[1] = in1[2] * in2[0] - in1[0] * in2[2];
    out[2] = in1[0] * in2[1] - in1[1] * in2[0];
}

    void calc_wheelspeed(){
        double surfacespeed0[3] = {0, 0, 0};   //表面速度ベクトル0
        double surfacespeed1[3] = {0, 0, 0};   //表面速度ベクトル1
        double surfacespeed2[3] = {0, 0, 0};   //表面速度ベクトル2

        matrix_product(omegavec, wheelpos0, surfacespeed0);
        matrix_product(omegavec, wheelpos1, surfacespeed1);
        matrix_product(omegavec, wheelpos2, surfacespeed2);

        for (int i = 0; i < 3;i++){
            wheelspeed[i] = 0.0;
        }
        for (int i = 0; i < 3;i++){
            wheelspeed[0] += surfacespeed0[i] * wheeldrive0[i];
            wheelspeed[0] += surfacespeed1[i] * wheeldrive1[i];
            wheelspeed[0] += surfacespeed2[i] * wheeldrive2[i];
        }
        for (int i = 0; i < 3;i++){
            wheelspeed[i] /= WHEEL_RADIUS;    //wheelspeed[i] = wheelspeed[i]/WHEEL_RADIUS
        }
}