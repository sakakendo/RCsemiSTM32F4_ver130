/***************************************************************************
 *	@�t�@�C����		:	07_RotaryENC.c
 *	@�T�v		:	���[�^���[�G���R�[�_�̃J�E���g����ǂݎ��CLCD�ɕ\������D
 *					�g�p����Ƃ��ɕK�v�ȏ����̓R�����g�̐擪��**�����Ă��܂��̂ŁC�g�p�̍ۂ�
 *					�K���L������悤�ɂ��Ă��������D
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __07_ENC__

#include <stm32f4xx.h>
#include "timer.h"
#include "lcd.h"
#include "xprintf.h"
#include "rotary_encoder.h"	// **���ꂪ�K�v

int main(void)
{
	int enc[4] = {0};
	int i;

	SystemCoreClockUpdate();	// **�V�X�e���N���b�N������������
	TIM7_CMT_Init();	// **ENC2,3���g�p���邽�߂ɏ���������

	/* LCD�̏����� */
	xdev_out(LCD_DrawChar);	// 1�����\������֐���o�^���Ă������ƂŁC xprintf�֐��ł̕\�����\�ɂȂ�D
	LCD_Init();
	LCD_Clear();
	LCD_LocateChar(0, 0);

	/* ���[�^���[�G���R�[�_�̏����� */
	ENC0_Init();	// **ENC0�̏�����������
	ENC1_Init();	// **ENC1�̏�����������
	ENC2_Init();	// **ENC2�̏�����������
	ENC3_Init();	// **ENC3�̏�����������

	xprintf("[Sample No.6]\n");

	while(1)
	{
		LCD_LocateChar(0, 1);

		for(i = 0; i < 4; i++)
		{
			/* �������邱�ƂŁCENC_CheckCNT�̃I�[�o�[�t���[��h�~�ł���
			 * �������C���荞�݂�����ƃJ�E���g����葹�˂�\�������� */
			enc[i] += ENC_CheckCNT(i);
			ENC_ClearCNT(i);

			xprintf("ENC%d:%6d\n", i, enc[i]);
		}
	}
}

#endif /* __07_ENC__ */
