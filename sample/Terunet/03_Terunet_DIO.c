/***************************************************************************
 *	@�t�@�C����		:	08_RS485_MD.c
 *	@�T�v		:	LTC485���g�p����LPC�}�C�R���ƃV���A���ʐM���s���C���[�^�쓮���s�����߂�PWM
 *					�M�����o�͂��܂��D
 *					�g�p����Ƃ��ɕK�v�ȏ����̓R�����g�̐擪��**�����Ă��܂��̂ŁC�g�p�̍ۂ�
 *					�K���L������悤�ɂ��Ă��������D
 *					�����߂�LPC���ɂ��Ă�LPC_NO_1��LPC_NO_2�̂�rs485_master.h�Œ�`
 *					���Ă���̂�LPC��3�ȏ�ڑ����Ďg�p����ꍇ�͎����Œ�`���Ă��������D
 *	@�o�[�W����		:	1.0.0
 *	@�J����		:	���c�ߍ�
 *	@�g�p��	:	STM32F4DISCOVERY, LPC1114FN28-102, LTC485, MB_Ver2, CooCox CoIDE
 **************************************************************************/
#include "sample.h"

#ifdef __08_RS485_MD__

#include <stm32f4xx.h>
#include "lcd.h"
#include "xprintf.h"
#include "motherboard.h"
#include "timer.h"			// **���ꂪ�K�v�C�^�C���A�E�g�����ɗp����D
#include "terunet.h"		// **���ꂪ�K�v�C�f�[�^�𑗎�M����̂ɕK�v
#include "terunet_motorDriver.h"	// **���ꂪ�K�v�C���[�^���쓮����֐����g�����ߕK�v

#define LPC_NO_1 0x01
#define LPC_NO_2 0x02

int main(void)
{
	int dir = 1;
	int i;
	u8 recvData;

	SystemCoreClockUpdate();	// **�V�X�e���N���b�N������������
	TIM7_CMT_Init();	// delay���g�p���邽�߂ɏ���������

	/* LCD�̏����� */
	xdev_out(LCD_DrawChar);	// 1�����\������֐���o�^���Ă������ƂŁC xprintf�֐��ł̕\�����\�ɂȂ�D
	LCD_Init();
	LCD_Clear();
	LCD_LocateChar(0, 0);
	xprintf("[Sample No.8]\n");

	RS485_Init(RS485_BAUDRATE);	// **RS485�̏�����

	MB_RotarySW_Init();
	MB_PushSW_Init();

	while(1)
	{
		if(MB_PushSW_IsPushed())	dir = -1;
		else						dir =  1;

		RS485_Motor_Drive(LPC_NO_1, 0, dir *  MB_RotarySW_Check()*1, &recvData);	//1�ڂ�LPC�̃|�[�g0�ɏo��
		RS485_Motor_Drive(LPC_NO_1, 1, dir *  MB_RotarySW_Check()*2, &recvData);	//1�ڂ�LPC�̃|�[�g1�ɏo��
		RS485_Motor_Drive(LPC_NO_1, 2, dir *  MB_RotarySW_Check()*3, &recvData);	//1�ڂ�LPC�̃|�[�g2�ɏo��
		RS485_Motor_Drive(LPC_NO_1, 3, dir *  MB_RotarySW_Check()*4, &recvData);	//1�ڂ�LPC�̃|�[�g3�ɏo��
		RS485_Motor_Drive(LPC_NO_1, 4, dir *  MB_RotarySW_Check()*5, &recvData);	//1�ڂ�LPC�̃|�[�g4�ɏo��
		RS485_Motor_Drive(LPC_NO_1, 5, dir *  MB_RotarySW_Check()*6, &recvData);	//1�ڂ�LPC�̃|�[�g5�ɏo��
		RS485_Motor_Drive(LPC_NO_1, 6, dir * -MB_RotarySW_Check()*6, &recvData);	//1�ڂ�LPC�̃|�[�g6�ɏo��
		RS485_Motor_Drive(LPC_NO_1, 7, RS485_BRAKEVALUE, &recvData);				//1�ڂ�LPC�̃|�[�g7�ɏo��

		for(i = 0; i < 8; i++)	RS485_Motor_Drive(LPC_NO_2, i, dir * MB_RotarySW_Check()*6, &recvData);	//2�ڂ�LPC�̃|�[�g���ׂĂɏo��
	}
}

#endif /* __08_RS485_MD__ */
