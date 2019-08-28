// 全てのcppファイルにインクルードする
// 外部変数やファイル間で使用する関数を記述

#ifndef _COMMON_H_  // ヘッダファイルを重複してインクルード
#define _COMMON_H_  // しないためのifdef文

#include <mbed.h>
#include <BNO055.h>

#define PI 3.14159265358979

// main.cpp
#define MAIN_LOOP_TIME_MS 100    // メイン関数のループの周期[ms]

// interface.cpp
extern DigitalOut myled1;
extern Serial pc;
//extern InterruptIn button;
void Push();
void Pull();
void wait_button();
void Keyboard();
void interface_init();

// motor.cpp
void motor_init();
void motorspeed(double[3]);

// encoder.cpp
#define SUMPLING_TIME_US 50000  // エンコーダのサンプリング周期[μs]
extern int count_now[3]; // [count]
extern int delta_now[3]; // [count/sumpling_interval]
extern double delta_stock[3]; // [count/sumpling_interval]
extern int en_mode;
void encoder_init();
void EncoderLoop(); // 100000μsおきに実行される　エンコーダの読み取りやそこから制御を与えるコードをかく

// anglecontrol.cpp
extern double rotvector[4]; // 傾きの回転ベクトル
void bno_init();
void readangle();
void set_spin();

// toritu.cpp
extern double omegavec[3];  // 球を回転させる角速度ベクトル
extern double wheelspeed[3];
void calc_wheelspeed();

// motor_PID
extern double speed_test[3];
extern double en_speed[3];
void motor_pid(double speedref[3]);

#endif