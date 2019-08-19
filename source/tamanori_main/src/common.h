// 全てのcppファイルにインクルードする
// 外部変数やファイル間で使用する関数を記述

#ifndef _COMMON_H_  // ヘッダファイルを重複してインクルード
#define _COMMON_H_  // しないためのifdef文

#include <mbed.h>

// interface.cpp
extern Serial pc;
extern InterruptIn button;
void Push();
void Pull();
void Keyboard();

// motor.cpp
void motor_init();
void motorspeed(double[3]);

// encoder.cpp
// エンコーダのサンプリング周期[μs]
#define SUMPLING_TIME_US 50000
extern int count_now[3];
extern int delta_now[3];
extern double delta_stock[3];
extern int en_mode;
void encoder_init();
void EncoderLoop();//50000μsおきに実行される　エンコーダの読み取りやそこから制御を与えるコードをかく

// anglecontrol.cpp
void bno_init();

#endif