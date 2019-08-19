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
}

