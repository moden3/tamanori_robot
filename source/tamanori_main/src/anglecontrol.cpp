// BNOを読み取って角度制御
#include "common.h"
#include "BNO055.h"

BNO055 bno(PB_7, PB_8); // SDA,SCL

// 初期設定
void bno_init(){
    bno.setmode(OPERATION_MODE_NDOF);
}

// 四元数の読み込み
double quat[4]; // [x,y,z,w]
double rotvector[4];  // [x,y,z,theta]
double oldrotvector[4] = {0, 0, 0, 0};
double rotspeed[3] = {0, 0, 0};

// BNOから回転を読み取って変換
void readangle(){
    bno.get_quat();
    quat[0] = bno.quat.x;
    quat[1] = bno.quat.y;
    quat[2] = bno.quat.z;
    quat[3] = bno.quat.w;
    rotvector[0] = quat[1]/sqrt(1.0-quat[0]*quat[0]);
    rotvector[1] = quat[2]/sqrt(1.0-quat[0]*quat[0]);
    rotvector[2] = quat[3]/sqrt(1.0-quat[0]*quat[0]);
    rotvector[3] = 2*atan(sqrt(quat[0]*quat[0]+quat[1]*quat[1]+quat[2]*quat[2])/quat[3]);

    for (int i = 0; i < 4;i++){
        rotspeed[i] = rotvector[i] - oldrotvector[i];
    }
    for (int i = 0; i < 4; i++){
        oldrotvector[i] = rotvector[i];
    }
}

// 球の角速度を指定
void set_spin(){
    double K_theta = 0.5;   // 角度の比例ゲイン
    double K_omega = 0;     // 角速度の比例ゲイン
    for (int i = 0; i < 3;i++){
        omegavec[i] = rotvector[i] * K_theta + rotspeed[i] * K_omega;
    }
}
