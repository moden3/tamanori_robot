#include <mbed.h>
#include <BNO055.h>

Serial pc(USBTX,USBRX,115200);
BNO055 bno(PB_7, PB_8); // SDA,ACL

DigitalOut myled(LED1); // マイコンのLED

// 注意!
// bno.reset()する、または電源を入れると、
// 現在の角度を基準(オイラー角ならヨー角がゼロ,四元数ならzがゼロ)
// とした値を出力してくれるが、
// 動かしているうちに途中で元の座標系に戻ってしまうので不安定
// resetはなくていいかも


// bnoのオフセット値を格納[x,y,z,w]
double bno_quat_offset[4] = {0, 0, 0, 0};
// オフセット処理前の値を格納
double bno_quat_raw[4] = {0, 0, 0, 0};
// オフセット処理後の値を格納
double bno_quat[4] = {0, 0, 0, 0};


// 四元数を取得
void bno_get_quat(double quat_raw[4]){
  bno.get_quat();
  // 座標系を直す
  quat_raw[0] = -bno.quat.y; // x
  quat_raw[1] = bno.quat.x; // y
  quat_raw[2] = bno.quat.z; // z
  quat_raw[3] = bno.quat.w; // w

  // z成分を常に正にする
  /*if(quat_raw[2]<0){
    for (int i = 0; i < 4;i++)
      quat_raw[i] = -quat_raw[i];
  }*/
}

// 四元数の掛け算 q*p
void calc_quat(double q[4],double p[4],double ans[4]){
  ans[0] = q[3] * p[0] - q[2] * p[1] + q[1] * p[2] + q[0] * p[3];
  ans[1] = q[2] * p[0] + q[3] * p[1] - q[0] * p[2] + q[1] * p[3];
  ans[2] = -q[1] * p[0] + q[0] * p[1] + q[3] * p[2] + q[2] * p[3];
  ans[3] = -q[0] * p[0] - q[1] * p[1] - q[2] * p[2] + q[3] * p[3];
}

// オフセットの取得
void bno_set_offset(double offset[4], double quat_raw[4]){
  bno_get_quat(quat_raw);
  for (int i = 0; i < 4;i++)
    offset[i] = quat_raw[i];
  pc.printf("BNO_OFFSET\n");
}

// オフセット処理の計算
void bno_calc_offset(double offset[4], double quat_raw[4],double ans[4]){
  // 共役四元数
  double q[4] = {-offset[0], -offset[1], -offset[2], offset[3]};
  calc_quat(q, quat_raw, ans);
}

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

  // オフセットの取得
  bno_set_offset(bno_quat_offset, bno_quat_raw);
}


int main() {
  bno_init();

  while(1) {
    /*オイラー角*/
    bno.get_angles();
    pc.printf("[roll,pitch,yaw] = [%.2f  %.2f  %.2f]\n", bno.euler.roll, bno.euler.pitch, bno.euler.yaw);
    
    /*四元数*/
    bno_get_quat(bno_quat_raw);
    bno_calc_offset(bno_quat_offset, bno_quat_raw, bno_quat);

    //pc.printf("quaternion = %.3f : %.3f : %.3f : %.3f", bno_quat[0], bno_quat[1], bno_quat[2], bno_quat[3]);
    //pc.printf(" :: %.3f : %.3f : %.3f : %.3f\n", bno_quat_raw[0], bno_quat_raw[1], bno_quat_raw[2], bno_quat_raw[3]);

    wait(0.1);
	 }
}
