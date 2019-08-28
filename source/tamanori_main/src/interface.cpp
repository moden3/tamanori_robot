// キーボード入力やマイコンのユーザーボタンに関する関数
#include "common.h"

DigitalOut myled1(LED1);  // マイコンのLED
Serial pc(USBTX, USBRX);  // PCとのシリアル通信
InterruptIn button(USER_BUTTON);  // ユーザーボタンの割り込み関数
DigitalIn UB(USER_BUTTON);  // ユーザーボタンの入力

// ユーザーボタンを押したときに呼び出される関数
void Push(){
  pc.printf("ON\n");
  myled1 = 1;
}

// ユーザーボタンを引いたときに呼び出される関数
void Pull(){
  pc.printf("OFF\n");
  myled1 = 0;
}

// ユーザーボタンを待機する関数
void wait_button(){
  pc.printf("Push Button\n");
  while(UB){
    wait(0.1);
  }
  pc.printf("\nSTART\n\n");
  wait(0.1);
}

// キーボードを入力したときに呼び出される関数
void Keyboard(){
  char msg;
  msg = pc.getc();  // キーボードの情報を取得
  static double duty[3]={0,0,0};
  switch(msg){
    case '1':
      duty[0]+=0.05;
      break;
    case '2':
      duty[0]-=0.05;
      break;
    case '3':
      duty[1]+=0.05;
      break;
    case '4':
      duty[1]-=0.05;
      break;
    case '5':
      duty[2]+=0.05;
      break;
    case '6':
      duty[2]-=0.05;
      break;
    case '7':
      en_mode += 1;
      if(en_mode > 6){
        en_mode = 0;
      }
      break;
    case 'z':
      speed_test[0] += PI;
      pc.printf("speed_0 = %.1f\n", speed_test[0]);
      break;
    case 'x':
      speed_test[0] -= PI;
      pc.printf("speed_0 = %.1f\n", speed_test[0]);
      break;
    case 'c':
      speed_test[1] += PI;
      pc.printf("speed_1 = %.1f\n", speed_test[1]);
      break;
    case 'v':
      speed_test[1] -= PI;
      pc.printf("speed_1 = %.1f\n", speed_test[1]);
      break;
    case 'b':
      speed_test[2] += PI;
      pc.printf("speed_2 = %.1f\n", speed_test[2]);
      break;
    case 'n':
      speed_test[2] -= PI;
      pc.printf("speed_2 = %.1f\n", speed_test[2]);
      break;
    case '0':
      for(int i=0;i<3;i++){
        duty[i] = 0.0;
        speed_test[i] = 0.0;
        pc.printf("\nreset\n\n");
      }
      break;
    default:
      break;
  }
  //motorspeed(duty);
  //pc.printf("duty = %.3f : %.3f : %.3f \n",duty[0],duty[1],duty[2]);
}

// 割り込み関数やシリアル通信の設定の初期化
void interface_init(){
  button.fall(Push);  // ボタンを押したときの処理
  button.rise(Pull);  // ボタンを引いたときの処理

  //pc.baud(115200);
  pc.attach(Keyboard, Serial::RxIrq); // キーボード入力をシリアル通信で取得
}