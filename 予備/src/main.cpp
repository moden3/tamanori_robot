// メイン関数
#include "common.h"

void Initialize();
void MainLoop();

int main() {
  Initialize();

  while(1) {
    MainLoop();
    wait_ms(100);
  }
}


void Initialize(){
  button.fall(Push);  // ボタンを押したときの処理
  button.rise(Pull);  // ボタンを引いたときの処理

  motor_init();
  encoder_init();
  bno_init();

  pc.attach(Keyboard, Serial::RxIrq); // ボタンを押したときの処理
}

void MainLoop(){
  switch(en_mode){
    case 1:
      pc.printf("count = %d, : %d, : %d\n",count_now[0],count_now[1],count_now[2]);
      break;
    case 2:
      pc.printf("delta_now = %d, : %d, : %d\n",delta_now[0],delta_now[1],delta_now[2]);
      break;
    case 3:
      pc.printf("delta_stock = %.1f, : %.1f, : %.1f\n",delta_stock[0],delta_stock[1],delta_stock[2]);
      break;
  }
}