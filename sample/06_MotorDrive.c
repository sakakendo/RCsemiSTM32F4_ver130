/***************************************************************************
 *	@�t�@�C����		:	06_MotorDrive.c
 *	@�T�v		:	DIGITAL-IO���烂�[�^�쓮�̂��߂�PWM�M�����o�͂��܂��D
 *					�g�p����Ƃ��ɕK�v�ȏ����̓R�����g�̐擪��**�����Ă��܂��̂ŁC�g�p�̍ۂ�
 *					�K���L������悤�ɂ��Ă��������D
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __06_MD__

#include <stm32f4xx.h>
#include "motherboard.h"
#include "timer.h"
#include "digitalIO.h"	// **���ꂪ�K�v
#include "motor.h"		// **���ꂪ�K�v

int main(void)
{
	int i;
	int dir = 1;

	SystemCoreClockUpdate();	// **�V�X�e���N���b�N������������
	TIM7_CMT_Init();	// **PWM�𐶐����邽�߂ɕK�v

	DIO0_Init(0xFF, DIO_MODE_OUT);	// **���[�^�|�[�g�Ƃ��Ďg�p����s�����o�͂ɐݒ肵�Ă���
	DIO1_Init(0xFF, DIO_MODE_OUT);	// **���[�^�|�[�g�Ƃ��Ďg�p����s�����o�͂ɐݒ肵�Ă���
	DIO2_Init(0xFF, DIO_MODE_OUT);	// **���[�^�|�[�g�Ƃ��Ďg�p����s�����o�͂ɐݒ肵�Ă���

	MotorDriver_Init(0x0CCC);	// **12bit�Ń��[�^�|�[�g�̗L���E������ݒ肷��
								//   ���̏ꍇ�͂��ꂼ��̃|�[�g�̉��ʂQ�������ɂȂ�

	MB_RotarySW_Init();

	while(1)
	{
		if(MB_PushSW_IsPushed())	dir = -1;
		else						dir =  1;

		for (i = 0; i < 12; i++)
		{
			if(i%2)	Motor_Drive(i, dir * MB_RotarySW_Check()*6);
			else	Motor_Drive(i, dir * MB_RotarySW_Check()*6);
		}

		/* �����ɂ���Digital-IO�͕ʂ̋@�\�Ƃ��Ďg�p�ł��� */
		DIO_OutputPin(0, 0, 1);
		DIO_OutputPin(0, 1, 1);
		DIO_OutputPin(0, 2, 1);
		DIO_OutputPin(0, 3, 1);
		DIO_OutputPin(1, 0, 1);
		DIO_OutputPin(1, 1, 1);
		DIO_OutputPin(1, 2, 1);
		DIO_OutputPin(1, 3, 1);
		DIO_OutputPin(2, 0, 1);
		DIO_OutputPin(2, 1, 1);
		DIO_OutputPin(2, 2, 1);
		DIO_OutputPin(2, 3, 1);
	}
}

#endif /* __06_MD__ */
