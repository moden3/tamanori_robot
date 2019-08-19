#include <mbed.h>

DigitalOut myled1(LED1);  // マイコンのLED
Serial pc(USBTX, USBRX);  // PCとのシリアル通信
InterruptIn button(USER_BUTTON);  // ユーザーボタンの設定

PwmOut pulsepin(PA_15);  // パルス入力
DigitalOut pin1(PC_10);  // 正転逆転の入力ピン1
DigitalOut pin2(PC_3);  // 正転逆転の入力ピン2
// A15:B14:A01
// C10:B12:C05
// C03:B15:A04


void Push(){  // ユーザーボタンを押したときに呼び出される関数
  pc.printf("ON\n");
  myled1 = 1;
}

void Pull(){  // ユーザーボタンを引いたときに呼び出される関数
  pc.printf("OFF\n");
  myled1 = 0;
}

double dt = 10;     // パルスの周期[ms]
double duty = 0.1;  // デューティー比

void CallBack(){  // キーボードを入力したときに呼び出される関数
  char msg;
  msg = pc.getc();  // キーボードの情報を取得
  pc.putc(msg);
  if(msg=='u'){     // スピードを上げる
    duty += 0.1;
    pc.printf("speed up : duty= %f \n",duty);
  }
  if(msg=='d'){     // スピードを下げる
    duty -= 0.1;
    pc.printf("speed down : duty= %f \n",duty);
  }
  if(msg=='1'){     // 停止
    pin1 = 0;
    pin2 = 0;
  }
  if(msg=='2'){     // 正転
    pin1 = 0;
    pin2 = 1;
  }
  if(msg=='3'){     // 逆転
    pin1 = 1;
    pin2 = 0;
  }
  if(msg=='4'){     // ブレーキ
    pin1 = 1;
    pin2 = 1;
  }
  pulsepin.pulsewidth_ms(dt * duty);
}

int main() {
  button.fall(Push);  // ボタンを押したときの処理
  button.rise(Pull);  // ボタンを引いたときの処理

  pc.attach(CallBack, Serial::RxIrq); // ボタンを押したときの処理

  pin1 = 1;
  pin2 = 0;

  pulsepin.period_ms(dt);             // パルス周期の設定
  pulsepin.pulsewidth_ms(dt * duty);  // オン時間の設定

  while(1){
    wait(0.1);
  }
}