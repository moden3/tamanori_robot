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
extern int display_mode;    // PCで表示用のモード
extern DigitalOut myled1;
extern Serial pc;
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
#define EN_STOCK_RATE 0.30      // 速度の平滑化のパラメータ(割合)
extern int count_now[3];        // カウントの合計[count]
extern int delta_now[3];        // カウントの差分(カウント速度)[count/sumpling_interval]
extern double delta_stock[3];   // 平滑化したカウント速度[count/sumpling_interval]
void encoder_init();            // エンコーダの初期設定
void EncoderLoop();             // 50000μsおきに実行される

// bno_sensor.cpp
#define ROT_STOCK_RATE 0.30     // 角速度の平滑化のパラメータ(割合)
extern double bno_quat[4];      // オフセット処理後の値を格納
extern double rotvector[4];     // 傾きの回転ベクトル
extern double rotomega;         // 角速度[rad/s]
extern double rotomega_stock;   // 角速度の平滑化した値[rad/s]
void bno_init();                // BNOの初期設定
void bno_set_offset();          // 角度のオフセット値を設定
void readangle();               // 角度を読んで回転ベクトルと角速度を計算

// anglecontrol.cpp
void set_spin();

// toritu.cpp
extern double omegavec[3];      // 球を回転させる角速度ベクトル
extern double wheelspeed[3];    // 車輪の角速度(目標値)[rad/s]
void calc_wheelspeed();         // 車輪の角速度を計算

// motor_PID
extern int motor_flag;          // モータを動かすフラグ
extern double speed_test[3];    // PIDのテスト用の変数
extern double en_speed[3];      // 車輪の角速度(実際の値)[rad/s]
void motor_pid(double speedref[3]); // モータを動かす関数

#endif