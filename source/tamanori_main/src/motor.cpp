// ���[�^�̓���Ɋւ���֐��ƕϐ�
#include "common.h"

// �M���s���̐ݒ�(pwm�s��1�Ɛ��]�t�]�؂�ւ��s��2��)
// �z��̗v�f3�����ꂼ��̃��[�^�ɑΉ�
// pwm�s��
PwmOut motorpwm[3] = {
    PwmOut(PB_14),  // �O�̃��[�^
    PwmOut(PA_15),  // �E���̃��[�^
    PwmOut(PA_1)   // �����̃��[�^
};
// �X�C�b�`�s��1
DigitalOut motorsw1[3] = {
    DigitalOut(PB_12),
    DigitalOut(PC_10),
    DigitalOut(PC_5)
};
// �X�C�b�`�s��2
DigitalOut motorsw2[3] = {
    DigitalOut(PB_15),
    DigitalOut(PC_3),
    DigitalOut(PA_4)
};

// �p���X�̎���[ms]
double motorperiod_ms = 10;

// �������p�̊֐�
void motor_init() {
  // �p���X�����̐ݒ�
  for(int i=0;i<3;i++){
    motorpwm[i].period_ms(motorperiod_ms);
  }  // �I�����Ԃ̐ݒ�
}

// �f���[�e�B�[��(-1~1)���w�肵�ă��[�^���x��ύX
void motorspeed(double duty[3]){
  for(int i=0;i<3;i++){
    if(duty[i]>=0){
      motorsw1[i] = 0;
      motorsw2[i] = 1;
      motorpwm[i].pulsewidth_ms(motorperiod_ms*duty[i]);
    }else{
      motorsw1[i] = 1;
      motorsw2[i] = 0;
      motorpwm[i].pulsewidth_ms(-motorperiod_ms*duty[i]);
    }
  }
}
