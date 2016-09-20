/***************************************************************************
 *	@�t�@�C����		:	terunet_common.c
 *	@�T�v		:	Terunet�ʐM�ŋ��ʕ����ƂȂ�@�\�̃R�}���h�Ɗ֐���񋟂���D
 *	@�o�[�W����		:	1.0.0
 *	@�J����		:	�����P��
 *				:	�L�l�N�g
 *				:	���c�ߍ�
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "terunet.h"
#include "terunet_common.h"

int Terunet_ReadSlaveAddr(u8 addr, u8* buff)
{
	Terunet_SendFrame(addr, TerunetCmd_ReadSlaveAddr, 0, 0);
	return Terunet_ReceiveFrame(buff, TerunetCmd_ReadSlaveAddr);
}

int Terunet_ReadSystemVersion(u8 addr, u8* buff)
{
	Terunet_SendFrame(addr, TerunetCmd_ReadSystemVersion, 0, 0);
	return Terunet_ReceiveFrame(buff, TerunetCmd_ReadSystemVersion);
}
