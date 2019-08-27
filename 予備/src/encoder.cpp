// エンコーダの読み取りに関する関数と変数
#include "common.h"

// 信号ピンの設定
// エンコーダ3つ(0~2)のA相とB相
#define EN0A PC_0
#define EN0B PB_0
#define EN1A PA_9
#define EN1B PB_4
#define EN2A PA_7
#define EN2B PC_7

DigitalIn encoder[3][2]={
    {DigitalIn(EN0A),DigitalIn(EN0B)},
    {DigitalIn(EN1A),DigitalIn(EN1B)},
    {DigitalIn(EN2A),DigitalIn(EN2B)}
};
// A相の立ち上がりを見る
InterruptIn switchevent[3]={
    InterruptIn(EN0A),
    InterruptIn(EN1A),
    InterruptIn(EN2A)
};

// タイマー割込み
Ticker timer;

// 現在のエンコーダのカウント数を記録
int count_now[3] = {0,0,0};
// 前回サンプリングしたときのカウント数
int count_old[3] = {0,0,0};

// カウント数の差分を記録
int delta_now[3] = {0,0,0};
// 過去の差分データに対して現在のデータが影響する割合を指定
#define STOCK_RATE 0.40
double delta_stock[3] = {0,0,0};

// A相が立ち上がった時の処理
void en0_rise(){
    if(encoder[0][1]==1)
        count_now[0]++;
    else
        count_now[0]--;
}
void en1_rise(){
    if(encoder[1][1]==1)
        count_now[1]++;
    else
        count_now[1]--;
}
void en2_rise(){
    if(encoder[2][1]==1)
        count_now[2]++;
    else
        count_now[2]--;
}

// A相が立ち下がった時の処理
void en0_fall(){
    if(encoder[0][1]==1)
        count_now[0]--;
    else
        count_now[0]++;
}
void en1_fall(){
    if(encoder[1][1]==1)
        count_now[1]--;
    else
        count_now[1]++;
}
void en2_fall(){
    if(encoder[2][1]==1)
        count_now[2]--;
    else
        count_now[2]++;
}

// カウント速度を記録
void calc_speed(){
    for(int i=0;i<3;i++){
        // カウント数の差分
        delta_now[i] = count_now[i] - count_old[i];
        // count_oldの更新
        count_old[i] = count_now[i];
        // カウント速度の平滑化
        delta_stock[i] = (double)delta_now[i]*STOCK_RATE
                        +delta_stock[i]*(1-STOCK_RATE);
    }
    // 制御周期のループ
    EncoderLoop();
}

// 初期化用の関数
void encoder_init(){
    timer.attach_us(&calc_speed, SUMPLING_TIME_US);
    switchevent[0].rise(en0_rise);
    switchevent[1].rise(en1_rise);
    switchevent[2].rise(en2_rise);
    //switchevent[0].fall(en0_rise);
    //switchevent[1].fall(en1_rise);
    //switchevent[2].fall(en2_rise);
}

// PC表示用のモード
// 0:表示なし,1:count_now,2:delta_now,3:delta_stock
int en_mode = 0;

// 制御周期のループ
void EncoderLoop(){
}