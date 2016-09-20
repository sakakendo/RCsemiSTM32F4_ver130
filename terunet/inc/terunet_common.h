/***************************************************************************
 *	@�t�@�C����		:	terunet_common.h
 *	@�T�v		:	Terunet�ʐM�ŋ��ʕ����ƂȂ�@�\�̃R�}���h�Ɗ֐���񋟂���D
 *	@�o�[�W����		:	1.0.0
 *	@�J����		:	�����P��
 *				:	�L�l�N�g
 *				:	���c�ߍ�
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#ifndef __TERUNET_COMMON_H__
#define __TERUNET_COMMON_H__

#include <stm32f4xx.h>

typedef enum
{
	TerunetCmd_ReadSlaveAddr = 0x01,
	TerunetCmd_ReadSystemVersion,
	TerunetCmd_Head
} eTerunetCmdList_common_t;

extern int Terunet_ReadSlaveAddr(u8 addr, u8* buff);
extern int Terunet_ReadSystemVersion(u8 addr, u8* buff);

#endif /* __TERUNET_COMMON_H__ */
