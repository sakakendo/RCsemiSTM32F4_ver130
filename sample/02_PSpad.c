/***************************************************************************
 *	@�t�@�C����		:	02_PSpad.c
 *	@�T�v		:	PS�R���g���[������{�^���C�X�e�B�b�N�̏����󂯎��CLCD�ɕ\�����܂��D
 *					USART2��Bluetooth�ŁCUSART3���d�b���ł���C���ꂼ��v���O�����̏�����
 *					���قȂ�̂Œ��ӂ��Ă��������D
 *					�g�p����Ƃ��ɕK�v�ȏ����̓R�����g�̐擪��**�����Ă��܂��̂ŁC�g�p�̍ۂ�
 *					�K���L������悤�ɂ��Ă��������D
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __02_PSPAD__

#include <stm32f4xx.h>
#include "lcd.h"
#include "xprintf.h"
#include "timer.h"	// **���ꂪ�K�v
#include "usart.h"	// **���ꂪ�K�v
#include "pspad.h"	// **���ꂪ�K�v

// 90ms���炢���œK
#define LCD_REDRAW_CYCLE_MS	90

/* �ǂ̃|�[�g��PS�R���g���[�����q������
 * �R�����g�A�E�g�ɂĐ؂�ւ��Ă������� */
#define PSPAD_BT	1	// Bluetooth
//#define PSPAD_RJ12	1	// �d�b��

int main(void)
{
	int time0 = 0;

	psdata_format_t psdata;	// **�R���g���[���̏����i�[����\����

	SystemCoreClockUpdate();	// **�V�X�e���N���b�N������������

	TIM7_CMT_Init();	// **�^�C���A�E�g���邽�߂ɕK�v

	/* LCD�̏����� */
	xdev_out(LCD_DrawChar);
	LCD_Init();
	LCD_Clear();
	LCD_LocateChar(0, 0);

	xprintf("Now connecting...\n");

#if defined(PSPAD_BT)
	USART2_Init(BT_BAUDRATE, -1);	// **�����ԐM�Ȃ��ŏ�����
	USART2_BDSlave_Init(0);			// **�R���g���[�����R�l�N�g����܂Ń��[�v����
#elif defined(PSPAD_RJ12)
	USART3_Init(BT_BAUDRATE, -1);	// **�����ԐM�Ȃ��ŏ�����
	USART3_BDSlave_Init(0);			// **�R���g���[�����R�l�N�g����܂Ń��[�v����
#endif

	while(1)
	{
#if		defined(PSPAD_BT)
		USART2_PSdata_Recv(&psdata);	// **�R���g���[���̏����󂯎��
#elif	defined(PSPAD_RJ12)
		USART3_PSdata_Recv(&psdata);	// **�R���g���[���̏����󂯎��
#endif

		/* �ĕ`��̏��� */
		if(SystemTimer_ms_Check() - time0 >= LCD_REDRAW_CYCLE_MS)
		{
			time0 = SystemTimer_ms_Check();
			LCD_Clear();
		}

		/* �ȉ��̂悤��psdata_format_t�^�̕ϐ���psdata�Ƃ����Ƃ��C
		 * �e�{�^���Ȃǂ̏���PS_����n�܂�}�N���ŏ����󂯎���D */

		LCD_LocateChar(0, 0);

		xprintf("[STICK_L/STICK_R]\nX:%2d/Y:%2d\nX:%2d/Y:%2d\n", PS_STICK_LX(psdata), PS_STICK_LY(psdata)
												  	  	  	   , PS_STICK_RX(psdata), PS_STICK_RY(psdata));

		xprintf("[The Button]\n");
		if(PS_B_R1		(psdata))	xprintf("R1\n");
		if(PS_B_R2		(psdata))	xprintf("R2\n");
		if(PS_B_L1		(psdata))	xprintf("L1\n");
		if(PS_B_L2		(psdata))	xprintf("L2\n");
		if(PS_B_TRIANGLE(psdata))	xprintf("TRIANGLE\n");
		if(PS_B_CIRCLE	(psdata))	xprintf("CIRCLE\n");
		if(PS_B_CROSS	(psdata))	xprintf("CROSS\n");
		if(PS_B_SQUARE	(psdata))	xprintf("SQUARE\n");
		if(PS_B_START	(psdata))	xprintf("START\n");
		if(PS_B_SELECT	(psdata))	xprintf("SELECT\n");
		if(PS_B_ARROW_U	(psdata))	xprintf("ARROW_U\n");
		if(PS_B_ARROW_R	(psdata))	xprintf("ARROW_R\n");
		if(PS_B_ARROW_D	(psdata))	xprintf("ARROW_D\n");
		if(PS_B_ARROW_L	(psdata))	xprintf("ARROW_L\n");
		if(PS_B_STICK_R (psdata))	xprintf("STICK_R\n");
		if(PS_B_STICK_L (psdata))	xprintf("STICK_L\n");
	}
}

#endif /* __02_PSPAD__ */
