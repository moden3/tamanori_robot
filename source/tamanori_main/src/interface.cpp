// キーボード入力やマイコンのユーザーボタンに関する関数
#include "common.h"

int display_mode = 0; // PCで表示用のモード

DigitalOut myled1(LED1);  // マイコンのLED
Serial pc(USBTX, USBRX,115200);  // PCとのシリアル通信
InterruptIn button(USER_BUTTON);  // ユーザーボタンの割り込み関数
DigitalIn UB(USER_BUTTON);  // ユーザーボタンの入力

// ユーザーボタンを押したときに呼び出される関数
void Push(){
  //pc.printf("ON\n");
  if(motor_flag==0){
    motor_flag = 1;  // モータを動かすフラグを立てる
    pc.printf("\nSTART\n\n");
  }
  myled1 = 1;
}

// ユーザーボタンを引いたときに呼び出される関数
void Pull(){
  //pc.printf("OFF\n");
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

  switch(msg){
    // PC表示モードの切り替え
    case ' ':
      display_mode += 1;
      if(display_mode > 7)display_mode = 0;
      break;
    // BNOのオフセットを設定
    case 'q':
      bno_set_offset();
      break;
    // モータ動作テスト用の入力
    case '1':
      speed_test[0] += PI;
      pc.printf("speed_0 = %.1f\n", speed_test[0]);
      break;
    case '2':
      speed_test[0] -= PI;
      pc.printf("speed_0 = %.1f\n", speed_test[0]);
      break;
    case '3':
      speed_test[1] += PI;
      pc.printf("speed_1 = %.1f\n", speed_test[1]);
      break;
    case '4':
      speed_test[1] -= PI;
      pc.printf("speed_1 = %.1f\n", speed_test[1]);
      break;
    case '5':
      speed_test[2] += PI;
      pc.printf("speed_2 = %.1f\n", speed_test[2]);
      break;
    case '6':
      speed_test[2] -= PI;
      pc.printf("speed_2 = %.1f\n", speed_test[2]);
      break;
    // 停止操作
    case '0':
      // モータを止める
      motor_flag = 0;
      for(int i=0;i<3;i++)speed_test[i] = 0.0;
      // PCの表示を止める
      display_mode = 0;
      pc.printf("\nSTOP\n\n");
      break;
    // その他は入力した値を表示
    default:
      pc.putc(msg);
      break;
  }
}

// 割り込み関数やシリアル通信の設定の初期化
void interface_init(){
  button.fall(Push);  // ボタンを押したときの処理
  button.rise(Pull);  // ボタンを引いたときの処理

  pc.attach(Keyboard, Serial::RxIrq); // キーボード入力をシリアル通信で取得
}