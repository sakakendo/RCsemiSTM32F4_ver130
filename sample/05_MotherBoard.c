/***************************************************************************
 *	@�t�@�C����		:	05_MotherBoard.c
 *	@�T�v		:	MB���LED�C�v�b�V���X�C�b�`�C���[�^���[�X�C�b�`�𐧌䂵�܂��D
 *					�v�b�V���X�C�b�`�C���[�^���[�X�C�b�`�̏�Ԃ�LCD�ɕ\�����Ă��܂��D
 *					�g�p����Ƃ��ɕK�v�ȏ����̓R�����g�̐擪��**�����Ă��܂��̂ŁC�g�p�̍ۂ�
 *					�K���L������悤�ɂ��Ă��������D
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __05_MB__

#include <stm32f4xx.h>
#include "lcd.h"
#include "xprintf.h"
#include "timer.h"
#include "motherboard.h"	// **���ꂪ�K�v

// 90ms���炢���œK
#define LCD_REDRAW_CYCLE_MS	90

int main(void)
{
	int time0 = 0;

	SystemCoreClockUpdate();	// **�V�X�e���N���b�N������������
	TIM7_CMT_Init();

	/* LCD�̏����� */
	xdev_out(LCD_DrawChar);	// 1�����\������֐���o�^���Ă������ƂŁC xprintf�֐��ł̕\�����\�ɂȂ�D
	LCD_Init();
	LCD_Clear();

	/* MB�@�\�̏����� */
	MB_LED_Init();		// **LED���g���Ƃ����ꂪ�K�v
	MB_PushSW_Init();	// **�v�b�V���X�C�b�`���g���Ƃ����ꂪ�K�v
	MB_RotarySW_Init();	// **���[�^���[�X�C�b�`���g���Ƃ����ꂪ�K�v

	/* LED */
	MB_LED_TurnOn(0);
	MB_LED_TurnOff(1);

	while(1)
	{
		LCD_LocateChar(0, 0);

		/* �ĕ`��̏��� */
		if(SystemTimer_ms_Check() - time0 >= LCD_REDRAW_CYCLE_MS)
		{
			time0 = SystemTimer_ms_Check();
			LCD_Clear();
		}

		/* LED */
		MB_LED_Toggle(0);
		MB_LED_Toggle(1);

		/* PushSW */
		xprintf("PushSW : ");
		if(MB_PushSW_IsPushed())	xprintf("Pushed\n");
		else						xprintf("Not Pushed\n");

		/* RotarySW */
		xprintf("RotarySW : 0x%x\n", MB_RotarySW_Check());

		delay_ms(100);
	}
}

#endif /* __05_MB__ */
