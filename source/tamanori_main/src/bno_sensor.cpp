// BNoを扱うための関数
#include "common.h"

BNO055 bno(PB_7, PB_8); // SDA,ACL

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
// 回転ベクトル
double rotvector[4] = {0,0,0,0};  // [x,y,z,theta]
// 角速度[rad/s]
double rotomega = 0.0;
double rotomega_stock = 0.0;    // 角速度を平滑化した値


// 四元数を取得
void bno_get_quat(){
  bno.get_quat();
  // 座標系を直す
  bno_quat_raw[0] = -bno.quat.y; // x
  bno_quat_raw[1] = bno.quat.x; // y
  bno_quat_raw[2] = bno.quat.z; // z
  bno_quat_raw[3] = bno.quat.w; // w

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

// オフセットの設定
void bno_set_offset(){
  bno_get_quat();
  for (int i = 0; i < 4;i++)
    bno_quat_offset[i] = bno_quat_raw[i];
  pc.printf("BNO_OFFSET\n");
}

// オフセット処理の計算
void bno_calc_offset(double offset[4], double quat_raw[4], double ans[4] = bno_quat){
  // 共役四元数
  double q[4] = {-offset[0], -offset[1], -offset[2], offset[3]};
  
  calc_quat(q, quat_raw, ans);
}

// 初期設定
void bno_init(){
  // BNOが接続できていなかったらLチカする
  myled1 = 1;
  if (!bno.check())
  {
    pc.printf("!!BNO_ERROR!!\n");
    while (1)
    {
      myled1 = !myled1;
      wait(0.1);
    }
  }
  myled1 = 0;
  pc.printf("BNO_CONNECTED\n");

  bno.setmode(OPERATION_MODE_NDOF);

  // オフセットの設定
  bno_set_offset();
}


// BNOから角度を読み取って回転ベクトルと角速度を計算
void readangle() {
    bno_get_quat();
    bno_calc_offset(bno_quat_offset, bno_quat_raw);

    // 回転ベクトルに変換
    // ゼロ割の防止
    double temp1=sqrt(1-bno_quat[3]*bno_quat[3]);
    if(temp1==0.0)temp1=0.00001;
    // 回転ベクトル(単位ベクトル)のxyz成分を計算
    rotvector[0] = bno_quat[0]/temp1;
    rotvector[1] = bno_quat[1]/temp1;
    rotvector[2] = bno_quat[2]/temp1;

    // ゼロ割の防止
    double temp2 = bno_quat[3];
    if(temp2==0.0)temp2=0.00001;
    // 回転角度θの計算
    double oldvector3 = rotvector[3];   // 更新前の値を記録
    rotvector[3]=2*atan(sqrt(bno_quat[0]*bno_quat[0]+bno_quat[1]*bno_quat[1]+bno_quat[2]*bno_quat[2])/temp2);

    // z成分を削除
    rotvector[2] = 0.0;
    rotvector[3] *= sqrt(rotvector[0] * rotvector[0] + rotvector[1] * rotvector[1]);

    // 角速度の計算[rad/s]
    rotomega = (rotvector[3] - oldvector3) / (double)MAIN_LOOP_TIME_MS * 1000.0;
    // 角速度の平滑化
    rotomega_stock = rotomega*ROT_STOCK_RATE+rotomega_stock*(1.0-ROT_STOCK_RATE);
}
