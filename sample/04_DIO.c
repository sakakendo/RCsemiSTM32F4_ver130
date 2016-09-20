/***************************************************************************
 *	@�t�@�C����		:	04_DIO.c
 *	@�T�v		:	DIGITAL-IOx�Ɉ�����ꂽHIGH/LOW��ǂݎ��CLCD�ɕ\��������C
 *					DIGITAL-IOx����HIGH/LOW���o�͂����肵�܂��D
 *					�g�p����Ƃ��ɕK�v�ȏ����̓R�����g�̐擪��**�����Ă��܂��̂ŁC�g�p�̍ۂ�
 *					�K���L������悤�ɂ��Ă��������D
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __04_DIO__

#include <stm32f4xx.h>
#include "lcd.h"
#include "timer.h"
#include "xprintf.h"
#include "digitalIO.h"	// **���ꂪ�K�v

int main(void)
{
	SystemCoreClockUpdate();	// **�V�X�e���N���b�N������������
	TIM7_CMT_Init();

	u8 d_in;
	int i;

	/* LCD�̏����� */
	xdev_out(LCD_DrawChar);	// 1�����\������֐���o�^���Ă������ƂŁC xprintf�֐��ł̕\�����\�ɂȂ�D
	LCD_Init();
	LCD_Clear();
	LCD_LocateChar(0, 0);

	xprintf("[Sample No.4]\n");

	/* DIGITAL-IO�̏����� */
	DIO0_Init(0xFF, DIO_MODE_OUT);	// **0xFF��0b11111111�C�܂�CDIO0��8�s�����ׂĂ��o�͂ɐݒ肷��D
	DIO1_Init(0xFF, DIO_MODE_IN);	// **0xFF��0b11111111�C�܂�CDIO0��8�s�����ׂĂ���͂ɐݒ肷��D
	DIO2_Init(0xFF, DIO_MODE_OUT);	// **0xFF��0b11111111�C�܂�CDIO0��8�s�����ׂĂ��o�͂ɐݒ肷��D

	/* �ȉ��̂悤�Ȃ��Ƃ��ł���
	DIO0_Init(0xF0, DIO_MODE_IN);	// **0xF0��0b11110000�C�܂�CDIO0�̏��4�s������͂ɐݒ肷��D
	DIO0_Init(0x0F, DIO_MODE_OUT);	// **0x0F��0b00001111�C�܂�CDIO0�̉���4�s�����o�͂ɐݒ肷��D
	DIO1_Init(0xF0, DIO_MODE_IN);	// **0xF0��0b11110000�C�܂�CDIO1�̏��4�s������͂ɐݒ肷��D
	DIO1_Init(0x0F, DIO_MODE_OUT);	// **0x0F��0b00001111�C�܂�CDIO1�̉���4�s�����o�͂ɐݒ肷��D
	DIO2_Init(0xF0, DIO_MODE_IN);	// **0xF0��0b11110000�C�܂�CDIO2�̏��4�s������͂ɐݒ肷��D
	DIO2_Init(0x0F, DIO_MODE_OUT);	// **0x0F��0b00001111�C�܂�CDIO2�̉���4�s�����o�͂ɐݒ肷��D
	*/

	while(1)
	{
		LCD_LocateChar(0, 1);

		/* �|�[�g0,2����M�����o�͂��� */
		for(i = 0; i < 8; i++)
		{
			DIO_OutputPin(0, i, 1);
			DIO_OutputPin(2, i, 1);
		}

		/* �|�[�g1�̊e�r�b�g���󂯎��� */
		d_in = DIO_CheckPin(1, 0) 	  | (DIO_CheckPin(1, 1)<<1) | (DIO_CheckPin(1, 2)<<2) | (DIO_CheckPin(1, 3)<<3) |
			  (DIO_CheckPin(1, 4)<<4) | (DIO_CheckPin(1, 5)<<5) | (DIO_CheckPin(1, 6)<<6) | (DIO_CheckPin(1, 7)<<7);

		xprintf("\r0x%02x", d_in);
	}
}

#endif /* __04_DIO__ */
