// キーボード入力やマイコンのユーザーボタンに関する関数
#include "common.h"

DigitalOut myled1(LED1);  // マイコンのLED
Serial pc(USBTX, USBRX);  // PCとのシリアル通信
InterruptIn button(USER_BUTTON);  // ユーザーボタンの設定

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
    case '0':
      for(int i=0;i<3;i++) duty[i]=0.0;
      break;
    case '7':
      switch(en_mode){
        case 0:
          en_mode = 1;
          break;
        case 1:
          en_mode = 2;
          break;
        case 2:
          en_mode = 3;
          break;
        case 3:
          en_mode = 0;
          break;
      }
      break;
    default:
      break;
  }
  motorspeed(duty);
  pc.printf("duty = %.3f : %.3f : %.3f \n",duty[0],duty[1],duty[2]);
}
