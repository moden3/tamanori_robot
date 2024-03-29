// メイン関数
#include "common.h"

void Initialize();
void MainLoop();

int main() {
  Initialize();

  while(1) {
    MainLoop();
    wait_ms(MAIN_LOOP_TIME_MS);
  }
}


void Initialize(){
  interface_init();
  bno_init();
  motor_init();
  
  encoder_init();
}


void MainLoop(){
  readangle();

  switch(display_mode){
    case 1:
      pc.printf("count = %d : %d : %d\n",count_now[0],count_now[1],count_now[2]);
      break;
    case 2:
      pc.printf("delta_stock[count] = %.1f : %.1f : %.1f\n",delta_stock[0],delta_stock[1],delta_stock[2]);
      break;
    case 3:
      pc.printf("en_speed[rad/s] = %.1f : %.1f : %.1f\n",en_speed[0],en_speed[1],en_speed[2]);
      break;
    case 4:
      pc.printf("rot_vector = [%.2f %.2f %.2f] : theta = %.2f\n", rotvector[0]*rotvector[3], rotvector[1]*rotvector[3], rotvector[2]*rotvector[3], rotvector[3]);
      break;
    case 5:
      pc.printf("rot_omega[rad/s] = %.2f\n",rotomega_stock);
      break;
    case 6:
      pc.printf("wheelspeed[rad/s] = %.1f : %.1f : %.1f\n",wheelspeed[0],wheelspeed[1],wheelspeed[2]);
      break;
  }
}