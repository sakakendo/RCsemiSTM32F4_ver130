/***************************************************************************
 *	@�t�@�C����		:	01_LCD.c
 *	@�T�v		:	MB��ɂ���LCD�̕\���e�X�g���s���܂��D
 *					�t�H���g�́Ctri_S_Font6x8_90.h���g�p���Ă���܂��D
 *					�g�p����Ƃ��ɕK�v�ȏ����̓R�����g�̐擪��**�����Ă��܂��̂ŁC�g�p�̍ۂ�
 *					�K���L������悤�ɂ��Ă��������D
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __01_LCD__

#include <stm32f4xx.h>
#include "lcd.h"		// **���ꂪ�K�v
#include "timer.h"		// **���ꂪ�K�v
#include "xprintf.h"	// **���ꂪ�K�v

int main(void)
{
	u8 cnt;

	SystemCoreClockUpdate();	// **�V�X�e���N���b�N������������

	TIM7_CMT_Init();	// **LCD_Init����delay_ms���g�p���邽�߂ɕK�v

	/* LCD�̏����� */
	xdev_out(LCD_DrawChar);	// 1�����\������֐���o�^���Ă������ƂŁC xprintf�֐��ł̕\�����\�ɂȂ�D
	LCD_Init();				// **LCD�̏�����
	LCD_Clear();			// **�\�����N���A����
	LCD_LocateChar(0, 0);	// ������`�悷����W���w�肷��

	for(cnt = 3; cnt > 0; cnt--)
	{
		xprintf("\r%d", cnt);	// \r�ŕ���������l�ɂ���D
		delay_ms(1000);
	}

	LCD_Clear();
	LCD_LocateChar(0, 0);

	xprintf("!! Hello World !!\n!! Yes, Kinect !!");	// \n�ŉ��s

	while(1)
	{
		cnt &= 0x3F;
		LCD_ScrollPixel(cnt++);	// �s�N�Z���P�ʂŏc�ɃX�N���[������
		delay_ms(100);
	}
}

#endif /* __01_LCD__ */
