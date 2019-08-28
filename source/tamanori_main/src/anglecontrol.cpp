// BNOを読み取って角度制御
#include "common.h"

BNO055 bno(PB_7, PB_8); // SDA,SCL

// 初期設定
void bno_init(){
    bno.reset();
    // BNOが接続できていなかったらLチカする
    if(!bno.check()){
        pc.printf("BNO_ERROR\n");
        while(1){
            myled1 = !myled1;
            wait(0.1);
        }
        pc.printf("BNO_CONNECTED");
    }
    myled1 = 0;
    bno.setmode(OPERATION_MODE_NDOF);
}

// 四元数の読み込み
double body_quat[4] = {0,0,0,0}; // [x,y,z,w]
double rotvector[4] = {0,0,0,0};  // [x,y,z,theta]
double oldrotvector[4] = {0, 0, 0, 0};
double rotdev = 0;

// BNOから四元数を読み取って回転ベクトルに変換
void readangle(){
    bno.setmode(OPERATION_MODE_NDOF);
    bno.get_quat();
    body_quat[0] = (double)bno.quat.x;
    body_quat[1] = (double)bno.quat.y;
    body_quat[2] = (double)bno.quat.z;
    body_quat[3] = (double)bno.quat.w;
    
    // ゼロ割の防止
    double temp1=sqrt(1.0-body_quat[3]*body_quat[3]);
    if(temp1==0.0)temp1=0.00001;
    
    rotvector[0] = body_quat[0]/temp1;
    rotvector[1] = -body_quat[1]/temp1;
    rotvector[2] = -body_quat[2]/temp1;

    // ゼロ割の防止
    double body_quat3 = body_quat[3];
    if(body_quat3==0.0) body_quat3=0.00001;

    rotvector[3] = 2*atan(sqrt(body_quat[0]*body_quat[0]+body_quat[1]*body_quat[1]+body_quat[2]*body_quat[2])/body_quat3);

    // arctanの処理(atanは-PI/2~PI/2までしか出力しないため)
    if(rotvector[3]<oldrotvector[3]-PI/2){
        rotvector[3] += PI;
    }else if(rotvector[3]>oldrotvector[3]+PI/2){
        rotvector[3] -= PI;
    }

    rotdev = rotvector[3] - oldrotvector[3] / (double)MAIN_LOOP_TIME_MS * 1000;  // 傾き角度の差分[rad/s]

    for (int i = 0; i < 4; i++){
        oldrotvector[i] = rotvector[i];
    }
}

// 球の角速度を指定
void set_spin(){
    double K_theta = 18.0;   // 角度の比例ゲイン
    double K_omega = 0;     // 角速度の比例ゲイン
    for (int i = 0; i < 3;i++){
        omegavec[i] = rotvector[i] * (rotvector[3] * K_theta + rotdev * K_omega);
    }
}
