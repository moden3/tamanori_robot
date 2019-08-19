// �L�[�{�[�h���͂�}�C�R���̃��[�U�[�{�^���Ɋւ���֐�
#include "common.h"

DigitalOut myled1(LED1);  // �}�C�R����LED
Serial pc(USBTX, USBRX);  // PC�Ƃ̃V���A���ʐM
InterruptIn button(USER_BUTTON);  // ���[�U�[�{�^���̐ݒ�

// ���[�U�[�{�^�����������Ƃ��ɌĂяo�����֐�
void Push(){
  pc.printf("ON\n");
  myled1 = 1;
}

// ���[�U�[�{�^�����������Ƃ��ɌĂяo�����֐�
void Pull(){
  pc.printf("OFF\n");
  myled1 = 0;
}

// �L�[�{�[�h����͂����Ƃ��ɌĂяo�����֐�
void Keyboard(){
  char msg;
  msg = pc.getc();  // �L�[�{�[�h�̏����擾
  static double duty[3]={0,0,0};
  switch(msg){
    case '1':
      duty[0]+=0.05;
      break;
    case '2':
      duty[0]-=0.05;
      break;
    case '3':
      duty[1]+=0.05;
      break;
    case '4':
      duty[1]-=0.05;
      break;
    case '5':
      duty[2]+=0.05;
      break;
    case '6':
      duty[2]-=0.05;
      break;
    case '0':
      for(int i=0;i<3;i++) duty[i]=0.0;
      break;
    case '7':
      switch(en_mode){
        case 0:
          en_mode = 1;
          break;
        case 1:
          en_mode = 2;
          break;
        case 2:
          en_mode = 3;
          break;
        case 3:
          en_mode = 0;
          break;
      }
      break;
    default:
      break;
  }
  motorspeed(duty);
  pc.printf("duty = %.3f : %.3f : %.3f \n",duty[0],duty[1],duty[2]);
}
