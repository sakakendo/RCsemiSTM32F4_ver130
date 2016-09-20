/***************************************************************************
 *	@�t�@�C����		:	terunet_motorDriver.h
 *	@�T�v		:	Terunet�ʐM�ɂă��[�^�h���C�o�𐧌䂷��D
 *	@�o�[�W����		:	1.0.0
 *	@�J����		:	�����P��
 *				:	�L�l�N�g
 *				:	���c�ߍ�
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#ifndef __TERUNET_MOTORDRIVER_H__
#define __TERUNET_MOTORDRIVER_H__

#include "terunet_common.h"

#define TERUNET_MD_BRAKEVALUE	32099

typedef enum
{
	TerunetCmd_MD_ReqSingleDrive = TerunetCmd_Head,
	TerunetCmd_MD_ReqMultiDrive,
	TerunetCmd_MD_SetFrequency,
	TerunetCmd_MD_ReadCurrent
} eTerunetCmdList_motorDriver_t;

extern int Terunet_MD_Drive(u8 addr, u8 ch, int duty, u8 recvData[]);

#endif /* __TERUNET_MOTORDRIVER_H__ */
