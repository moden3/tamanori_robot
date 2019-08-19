// �G���R�[�_�̓ǂݎ��Ɋւ���֐��ƕϐ�
#include "common.h"

// �M���s���̐ݒ�
// �G���R�[�_3��(0~2)��A����B��
#define EN0A PC_0
#define EN0B PB_0
#define EN1A PA_9
#define EN1B PB_4
#define EN2A PA_7
#define EN2B PC_7

DigitalIn encoder[3][2]={
    {DigitalIn(EN0A),DigitalIn(EN0B)},
    {DigitalIn(EN1A),DigitalIn(EN1B)},
    {DigitalIn(EN2A),DigitalIn(EN2B)}
};
// A���̗����オ�������
InterruptIn switchevent[3]={
    InterruptIn(EN0A),
    InterruptIn(EN1A),
    InterruptIn(EN2A)
};

// �^�C�}�[������
Ticker timer;

// ���݂̃G���R�[�_�̃J�E���g�����L�^
int count_now[3] = {0,0,0};
// �O��T���v�����O�����Ƃ��̃J�E���g��
int count_old[3] = {0,0,0};

// �J�E���g���̍������L�^
int delta_now[3] = {0,0,0};
// �ߋ��̍����f�[�^�ɑ΂��Č��݂̃f�[�^���e�����銄�����w��
#define STOCK_RATE 0.40
double delta_stock[3] = {0,0,0};

// A���������オ�������̏���
void en0_rise(){
    if(encoder[0][1]==1)
        count_now[0]++;
    else
        count_now[0]--;
}
void en1_rise(){
    if(encoder[1][1]==1)
        count_now[1]++;
    else
        count_now[1]--;
}
void en2_rise(){
    if(encoder[2][1]==1)
        count_now[2]++;
    else
        count_now[2]--;
}

// A�������������������̏���
void en0_fall(){
    if(encoder[0][1]==1)
        count_now[0]--;
    else
        count_now[0]++;
}
void en1_fall(){
    if(encoder[1][1]==1)
        count_now[1]--;
    else
        count_now[1]++;
}
void en2_fall(){
    if(encoder[2][1]==1)
        count_now[2]--;
    else
        count_now[2]++;
}

// �J�E���g���x���L�^
void calc_speed(){
    for(int i=0;i<3;i++){
        // �J�E���g���̍���
        delta_now[i] = count_now[i] - count_old[i];
        // count_old�̍X�V
        count_old[i] = count_now[i];
        // �J�E���g���x�̕�����
        delta_stock[i] = (double)delta_now[i]*STOCK_RATE
                        +delta_stock[i]*(1-STOCK_RATE);
    }
    // ��������̃��[�v
    EncoderLoop();
}

// �������p�̊֐�
void encoder_init(){
    timer.attach_us(&calc_speed, SUMPLING_TIME_US);
    switchevent[0].rise(en0_rise);
    switchevent[1].rise(en1_rise);
    switchevent[2].rise(en2_rise);
    //switchevent[0].fall(en0_rise);
    //switchevent[1].fall(en1_rise);
    //switchevent[2].fall(en2_rise);
}

// PC�\���p�̃��[�h
// 0:�\���Ȃ�,1:count_now,2:delta_now,3:delta_stock
int en_mode = 0;

// ��������̃��[�v
void EncoderLoop(){
}