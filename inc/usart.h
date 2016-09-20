/***************************************************************************
 *	@�t�@�C����		:	usart.h
 *	@�T�v		:	USART2, USART3�������⑗��M��񋟂���D
 *					USART2(Bluetooth)	TX:PD5 / RX:PD6
 *					USART3(�d�b��)		TX:PD8 / RX:PD9
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#ifndef __USART_H__
#define __USART_H__

/* �C���N���[�h	============================================================= */
#include <stm32f4xx.h>

/* �萔��`	============================================================= */
#define USART2_RECV_TIMEOUT_MS	200	// S��y�̊�
#define USART3_RECV_TIMEOUT_MS	200	// S��y�̊�

#define BT_BAUDRATE	9600

/* �֐��v���g�^�C�v�錾	===================================================== */
/* -------------------------------------------------
 * @�֐���			:	USART2_Init, USART3_Init
 * @�T�v				:	USART2, USART3������������
 * @����-baud		:	�{�[���[�g��ݒ肷��
 *�@          -autoforward		0	: USART2����ԐM����
 *�@          					1	: USART3����ԐM����
 *�@          					�ق�	: �ԐM���Ȃ�
 * @�߂�l			:	�Ȃ�
 * ---------------------------------------------- */
void USART2_Init(int baud, int autoforward);
void USART3_Init(int baud, int autoforward);

/* -------------------------------------------------
 * @�֐���	:	USART2_RecvByte, USART3_RecvByte
 * @�T�v		:	USART2, USART3����1[Byte]�̏����󂯎��
 * @����		:	�Ȃ�
 * @�߂�l	:	��M�����f�[�^
 * ---------------------------------------------- */
int USART2_RecvByte(void);
int	USART3_RecvByte(void);

/* -------------------------------------------------
 * @�֐���	:	USART2_RecvString, USART3_RecvString
 * @�T�v		:	USART2, USART3����max[Byte]�󂯎��A
 * 				������Ƃ��ĉ��߂���
 * @����-buf	:	�󂯎����������̊i�[��
 *�@          -max	:	������̒���[Byte]
 * @�߂�l	:	�G���[
 * ---------------------------------------------- */
int	USART2_RecvString(char *buf, int max);
int	USART3_RecvString(char *buf, int max);

/* -------------------------------------------------
 * @�֐���		:	USART2_SendByte, USART3_SendByte
 * @�T�v			:	USART2, USART3����1[Byte]���M����
 * @����-byte	:	���M����1[Byte]����
 * @�߂�l		:	�Ȃ�
 * ---------------------------------------------- */
void USART2_SendByte(u8 byte);
void USART3_SendByte(u8 byte);

/* -------------------------------------------------
 * @�֐���	:	USART2_SendString, USART3_SendString
 * @�T�v		:	USART2, USART3���當����𑗐M����
 * @����-buf	:	���M���镶����
 * @�߂�l	:	�Ȃ�
 * ---------------------------------------------- */
void USART2_SendString(char *str);
void USART3_SendString(char *str);

#endif /* __USART_H__ */
