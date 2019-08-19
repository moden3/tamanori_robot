// �S�Ă�cpp�t�@�C���ɃC���N���[�h����
// �O���ϐ���t�@�C���ԂŎg�p����֐����L�q

#ifndef _COMMON_H_  // �w�b�_�t�@�C�����d�����ăC���N���[�h
#define _COMMON_H_  // ���Ȃ����߂�ifdef��

#include <mbed.h>

// interface.cpp
extern Serial pc;
extern InterruptIn button;
void Push();
void Pull();
void Keyboard();

// motor.cpp
void motor_init();
void motorspeed(double[3]);

// encoder.cpp
// �G���R�[�_�̃T���v�����O����[��s]
#define SUMPLING_TIME_US 50000
extern int count_now[3];
extern int delta_now[3];
extern double delta_stock[3];
extern int en_mode;
void encoder_init();
void EncoderLoop();

#endif