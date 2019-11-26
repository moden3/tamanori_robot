#include <mbed.h>
#include <BNO055.h>

Serial pc(USBTX,USBRX,115200);
BNO055 bno(PB_7, PB_8); // SDA,SCL

DigitalOut myled(LED1); // マイコンのLED

// 初期処理
void bno_init(){
  //bno.reset();
  // BNOが接続できていなかったらLチカする
  myled = 1;
  if (!bno.check())
  {
    pc.printf("!!BNO_ERROR!!\n");
    while (1)
    {
      myled = !myled;
      wait(0.1);
    }
  }
  myled = 0;
  pc.printf("BNO_CONNECTED\n");

  bno.setmode(OPERATION_MODE_IMUPLUS); 
}

int main() {
  bno_init();

  while(1) {
    /*オイラー角*/
    bno.get_angles();
    pc.printf("[roll,pitch,yaw] = [%.2f  %.2f  %.2f]\n", bno.euler.roll, bno.euler.pitch, bno.euler.yaw);
    wait(0.1);
	 }
}
