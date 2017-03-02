#include "stm32f4xx.h"
#include "digitalIO.h"
#include "motor.h"
#include "timer.h"		// **���ꂪ�K�v
#include "servo.h"


#define __08_SERVO__
#ifdef __08_SERVO__

//debug�p�ϐ��@�֐��ɓ������񐔂��J�E���g
//irq		servo.c :: TIM2_IRQHandler
//main_g	main.c :: main()
//while_g	main.c :: while(1)
extern int irq;
int main_g=0,while_g=0;


int main(){
	main_g++;
 	SystemCoreClockUpdate();	// **�V�X�e���N���b�N������������
	TIM2_CMT_Init();
	DIO0_Init(0xFF, DIO_MODE_OUT);	// **���[�^�|�[�g�Ƃ��Ďg�p����s�����o�͂ɐݒ肵�Ă���
	while_g++;
	while(1)
	{
		Servo_Drive(20,20);
	}
	return 0;
}

#endif //__08_SERVO__
