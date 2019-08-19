#include <mbed.h>

DigitalOut myled1(LED1);  // �}�C�R����LED
Serial pc(USBTX, USBRX);  // PC�Ƃ̃V���A���ʐM
InterruptIn button(USER_BUTTON);  // ���[�U�[�{�^���̐ݒ�

PwmOut pulsepin(PA_15);  // �p���X����
DigitalOut pin1(PC_10);  // ���]�t�]�̓��̓s��1
DigitalOut pin2(PC_3);  // ���]�t�]�̓��̓s��2
// A15:B14:A01
// C10:B12:C05
// C03:B15:A04


void Push(){  // ���[�U�[�{�^�����������Ƃ��ɌĂяo�����֐�
  pc.printf("ON\n");
  myled1 = 1;
}

void Pull(){  // ���[�U�[�{�^�����������Ƃ��ɌĂяo�����֐�
  pc.printf("OFF\n");
  myled1 = 0;
}

double dt = 10;     // �p���X�̎���[ms]
double duty = 0.1;  // �f���[�e�B�[��

void CallBack(){  // �L�[�{�[�h����͂����Ƃ��ɌĂяo�����֐�
  char msg;
  msg = pc.getc();  // �L�[�{�[�h�̏����擾
  pc.putc(msg);
  if(msg=='u'){     // �X�s�[�h���グ��
    duty += 0.1;
    pc.printf("speed up : duty= %f \n",duty);
  }
  if(msg=='d'){     // �X�s�[�h��������
    duty -= 0.1;
    pc.printf("speed down : duty= %f \n",duty);
  }
  if(msg=='1'){     // ��~
    pin1 = 0;
    pin2 = 0;
  }
  if(msg=='2'){     // ���]
    pin1 = 0;
    pin2 = 1;
  }
  if(msg=='3'){     // �t�]
    pin1 = 1;
    pin2 = 0;
  }
  if(msg=='4'){     // �u���[�L
    pin1 = 1;
    pin2 = 1;
  }
  pulsepin.pulsewidth_ms(dt * duty);
}

int main() {
  button.fall(Push);  // �{�^�����������Ƃ��̏���
  button.rise(Pull);  // �{�^�����������Ƃ��̏���

  pc.attach(CallBack, Serial::RxIrq); // �{�^�����������Ƃ��̏���

  pin1 = 1;
  pin2 = 0;

  pulsepin.period_ms(dt);             // �p���X�����̐ݒ�
  pulsepin.pulsewidth_ms(dt * duty);  // �I�����Ԃ̐ݒ�

  while(1){
    wait(0.1);
  }
}