// 球の角速度を制御
#include "common.h"

// 球の角速度を指定
void set_spin(){
    double K_theta = 20.0;   // 角度の比例ゲイン
    double K_theta_I = 0.1;
    double K_omega = 0.0;    // 角速度の比例ゲイン

    static double theta_sum = 0.0;
    for (int i = 0; i < 3;i++){
        omegavec[i] = rotvector[i] * (rotvector[3] * K_theta+theta_sum); // + rotomega_stock * K_omega);
    }
}
