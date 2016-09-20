/***************************************************************************
 *	@�t�@�C����		:	03_ADC.c
 *	@�T�v		:	ANALOG-IN�Ɉ�����ꂽ�d����ǂݎ��CLCD�ɕ\�����܂��D
 *					�g�p����Ƃ��ɕK�v�ȏ����̓R�����g�̐擪��**�����Ă��܂��̂ŁC�g�p�̍ۂ�
 *					�K���L������悤�ɂ��Ă��������D
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __03_ADC__

#include <stm32f4xx.h>
#include "lcd.h"
#include "timer.h"
#include "xprintf.h"
#include "adc.h"	// **���ꂪ�K�v

/* �ǂ̃��[�h��ADC�����邩��
 * �R�����g�A�E�g�Ő؂�ւ��Ă������� */
#define ADC_MODE_SIGNLECONV	1	// �V���O�����[�h
//#define ADC_MODE_CONTSCAN	1	// �A���X�L�������[�h�CDMA(Direct Memory Access)�œǂݎ��

int main(void)
{
	SystemCoreClockUpdate();	// **�V�X�e���N���b�N������������
	TIM7_CMT_Init();

	int i;

	/* LCD�̏����� */
	xdev_out(LCD_DrawChar);
	LCD_Init();
	LCD_Clear();
	LCD_LocateChar(0, 0);

	/* ADC�̏����� */
#if defined(ADC_MODE_SIGNLECONV)
	ADC_Single_Init();	// **ADC���V���O�����[�h�ŏ���������
#elif defined(ADC_MODE_CONTSCAN)
	ADC_ContScan_Init();	// **ADC��A���X�L�������[�h�ŏ���������
#endif

	xprintf("[Sample No.3]\n");

	while(1)
	{
		LCD_LocateChar(0, 0);

		for(i = 0; i < 8; i++)
		{
			if(i%2 == 0)	xprintf("\n");
#if 	defined(ADC_MODE_SIGNLECONV)
			xprintf("%6d ", ADC_Single_Read(i));
#elif	defined(ADC_MODE_CONTSCAN)
			xprintf("%6d ", ADC_ContScan_Read(i));
#endif
		}
	}
}

#endif /* __02_ADC__ */
