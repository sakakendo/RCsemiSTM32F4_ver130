/***************************************************************************
 *	@ファイル名		:	usart.c
 *	@概要		:	USART2(Bluetooth), USART3(電話線)の
 *					初期化や送受信を提供する．
 *					USART2(Bluetooth)	TX:PD5 / RX:PD6
 *					USART3(電話線)		TX:PD8 / RX:PD9
 *	@バージョン		:	1.2.1
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

/* インクルード ======================================================= */
#include <stm32f4xx.h>
#include "usart.h"
#include "timer.h"

/* 定数定義 ======================================================== */
#define RECEIVERINGBUFFSIZE 16

/* グローバル変数  ==================================================== */
static volatile int recvPtr_USART2_in, recvPtr_USART2_out;
static volatile int recvPtr_USART3_in, recvPtr_USART3_out;
static u8 recvRingBuff_USART2[RECEIVERINGBUFFSIZE];
static u8 recvRingBuff_USART3[RECEIVERINGBUFFSIZE];
static int autoforward_USART2,autoforward_USART3;

/* -------------------------------------------------
 * @関数名			:	USART2_Init, USART3_Init
 * @概要				:	USART2, USART3を初期化する
 * @引数-baud		:	ボーレートを設定する
 *　          -autoforward		0	: USART2から返信する
 *　          					1	: USART3から返信する
 *　          					ほか	: 返信しない
 * @戻り値			:	なし
 * ---------------------------------------------- */
void USART2_Init(int baud, int autoforward)
{
	recvPtr_USART2_in = recvPtr_USART2_out = 0;
	autoforward_USART2 = autoforward;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate				= baud * (SystemCoreClock / 168000000);
	USART_InitStructure.USART_WordLength			= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits				= USART_StopBits_1;
	USART_InitStructure.USART_Parity				= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode					= USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel						= USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}
void USART3_Init(int baud, int autoforward)
{
	recvPtr_USART3_in = recvPtr_USART3_out = 0;
	autoforward_USART3 = autoforward;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate				= baud * (SystemCoreClock / 168000000);
	USART_InitStructure.USART_WordLength			= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits				= USART_StopBits_1;
	USART_InitStructure.USART_Parity				= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode					= USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel						= USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);
}

/* -------------------------------------------------
 * @関数名	:	USART2_RecvByte, USART3_RecvByte
 * @概要		:	USART2, USART3から1[Byte]の情報を受け取る
 * @引数		:	なし
 * @戻り値	:	受信したデータ
 * ---------------------------------------------- */
int USART2_RecvByte(void)
{
	int data;
	int time0;

	time0 = SystemTimer_ms_Check();
	while(recvPtr_USART2_out == recvPtr_USART2_in)
	{
		if((SystemTimer_ms_Check()-time0) > USART2_RECV_TIMEOUT_MS)	return -1;
	}
	data = recvRingBuff_USART2[recvPtr_USART2_out];
	switch(autoforward_USART2)
	{
	case 0:
		USART2_SendByte(data);
		break;
	case 1:
		USART3_SendByte(data);
		break;
	}
	recvPtr_USART2_out++;
	if(recvPtr_USART2_out == RECEIVERINGBUFFSIZE)	recvPtr_USART2_out = 0;
	return data;
}

int	USART3_RecvByte(void)
{
	int data;
	int time0;

	time0 = SystemTimer_ms_Check();
	while(recvPtr_USART3_out == recvPtr_USART3_in)
	{
		if((SystemTimer_ms_Check()-time0) > USART3_RECV_TIMEOUT_MS)	return -1;
	}
	data = recvRingBuff_USART3[recvPtr_USART3_out];
	switch(autoforward_USART3)
	{
	case 0:
		USART2_SendByte(data);
		break;
	case 1:
		USART3_SendByte(data);
		break;
	}
	recvPtr_USART3_out++;
	if(recvPtr_USART3_out == RECEIVERINGBUFFSIZE)	recvPtr_USART3_out = 0;
	return data;
}

/* -------------------------------------------------
 * @関数名	:	USART2_RecvString, USART3_RecvString
 * @概要		:	USART2, USART3からmax[Byte]受け取り、
 * 				文字列として解釈する
 * @引数-buf	:	受け取った文字列の格納先
 *　          -max	:	文字列の長さ[Byte]
 * @戻り値	:	エラー
 * ---------------------------------------------- */
int	USART2_RecvString(char *buf, int max)
{
	int i;
	for(i = 0; i < max-i; i++)
	{
		*buf = USART2_RecvByte();

		if(*buf == -1)	return -1;
		if(*buf == '\r')
		{
			*buf = 0;
			return i+1;
		}
		if(*buf == 0x08)
		{
			buf -= 2;
			i -= 2;
		}
		if(*buf != '\n')	buf++;
		else				i--;
	}
	*buf = 0;
	return i+1;
}

int	USART3_RecvString (char *buf, int max)
{
	int i;
	for(i = 0; i < max-i; i++)
	{
		*buf = USART3_RecvByte();

		if(*buf == -1)	return -1;
		if(*buf == '\r')
		{
			*buf = 0;
			return i+1;
		}
		if(*buf == 0x08)
		{
			buf -= 2;
			i -= 2;
		}
		if(*buf != '\n')	buf++;
		else				i--;
	}
	*buf = 0;
	return i+1;
}

/* -------------------------------------------------
 * @関数名		:	USART2_SendByte, USART3_SendByte
 * @概要			:	USART2, USART3から1[Byte]送信する
 * @引数-byte	:	送信する1[Byte]文字
 * @戻り値		:	なし
 * ---------------------------------------------- */
void USART2_SendByte(u8 byte)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	USART_SendData(USART2, byte);
}
void USART3_SendByte(u8 byte)
{
	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	USART_SendData(USART3, byte);
}

/* -------------------------------------------------
 * @関数名	:	USART2_SendString, USART3_SendString
 * @概要		:	USART2, USART3から文字列を送信する
 * @引数-buf	:	送信する文字列
 * @戻り値	:	なし
 * ---------------------------------------------- */
void USART2_SendString(char *str)
{
	while(*str)
	{
		if(*str++ == '\n')	USART2_SendByte('\r');
		else				USART2_SendByte(*str++);
	}
}
void USART3_SendString(char *str)
{
	while(*str)
	{
		if(*str++ == '\n')	USART3_SendByte('\r');
		else				USART3_SendByte(*str++);
	}
}

/* -------------------------------------------------
 * @関数名	:	USART2_IRQHandler, USART3_IRQHandler
 * @概要		:	USART2, USART3の受信割り込みルーチン
 * ---------------------------------------------- */
void USART2_IRQHandler(void)
{
	// 受信終了
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		recvRingBuff_USART2[recvPtr_USART2_in] = USART_ReceiveData(USART2);
		recvPtr_USART2_in++;
		if(recvPtr_USART2_in == RECEIVERINGBUFFSIZE)	recvPtr_USART2_in = 0;
	}
}
void USART3_IRQHandler(void)
{
	// 受信終了
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		recvRingBuff_USART3[recvPtr_USART3_in] = USART_ReceiveData(USART3);
		recvPtr_USART3_in++;
		if(recvPtr_USART3_in == RECEIVERINGBUFFSIZE)	recvPtr_USART3_in = 0;
	}
}
