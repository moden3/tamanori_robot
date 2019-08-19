// モータの動作に関する関数と変数
#include "common.h"

// 信号ピンの設定(pwmピン1つと正転逆転切り替えピン2つ)
// 配列の要素3つがそれぞれのモータに対応
// pwmピン
PwmOut motorpwm[3] = {
    PwmOut(PB_14),  // 前のモータ
    PwmOut(PA_15),  // 右後ろのモータ
    PwmOut(PA_1)   // 左後ろのモータ
};
// スイッチピン1
DigitalOut motorsw1[3] = {
    DigitalOut(PB_12),
    DigitalOut(PC_10),
    DigitalOut(PC_5)
};
// スイッチピン2
DigitalOut motorsw2[3] = {
    DigitalOut(PB_15),
    DigitalOut(PC_3),
    DigitalOut(PA_4)
};

// パルスの周期[ms]
double motorperiod_ms = 10;

// 初期化用の関数
void motor_init() {
  // パルス周期の設定
  for(int i=0;i<3;i++){
    motorpwm[i].period_ms(motorperiod_ms);
  }  // オン時間の設定
}

// デューティー比(-1~1)を指定してモータ速度を変更
void motorspeed(double duty[3]){
  for(int i=0;i<3;i++){
    if(duty[i]>=0){
      motorsw1[i] = 0;
      motorsw2[i] = 1;
      motorpwm[i].pulsewidth_ms(motorperiod_ms*duty[i]);
    }else{
      motorsw1[i] = 1;
      motorsw2[i] = 0;
      motorpwm[i].pulsewidth_ms(-motorperiod_ms*duty[i]);
    }
  }
}
