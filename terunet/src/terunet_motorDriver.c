/***************************************************************************
 *	@�t�@�C����		:	terunet_motorDriver.c
 *	@�T�v		:	Terunet�ʐM�ɂă��[�^�h���C�o�𐧌䂷��D
 *	@�o�[�W����		:	1.0.0
 *	@�J����		:	�����P��
 *				:	�L�l�N�g
 *				:	���c�ߍ�
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "terunet.h"
#include "terunet_common.h"
#include "terunet_motorDriver.h"
#include "terunet_slaveAddress.h"

/* -------------------------------------------------
 * @�֐���		:	Terunet_MD_Drive
 * @�T�v			:	Terunet�ɂ�PWM�̏���1�����M����
 * @����-addr	:	���M��̃A�h���X
 *�@          -ch		:	���[�^�ԍ�
 *�@          -duty	:	PWM�̃f���[�e�B��(%)
 * @�߂�l		:	RS485�Ŏ�M�����f�[�^
 * ---------------------------------------------- */
int Terunet_MD_Drive(u8 addr, u8 ch, int duty, u8 recvData[])
{
	u8 sendVal;
	u8 data[2];

	if(duty == TERUNET_MD_BRAKEVALUE)	sendVal = 127;
	else								sendVal = (u8)(duty&0xff);

	data[0] = ch;
	data[1] = sendVal;

	Terunet_SendFrame((TERUNET_BASEADDR_MD|(addr&0x0F)), TerunetCmd_MD_ReqSingleDrive, 2, data);
	return Terunet_ReceiveFrame(recvData, TerunetCmd_MD_ReqSingleDrive);
}
