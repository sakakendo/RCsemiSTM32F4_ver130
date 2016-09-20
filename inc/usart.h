/***************************************************************************
 *	@ファイル名		:	usart.h
 *	@概要		:	USART2, USART3初期化や送受信を提供する．
 *					USART2(Bluetooth)	TX:PD5 / RX:PD6
 *					USART3(電話線)		TX:PD8 / RX:PD9
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#ifndef __USART_H__
#define __USART_H__

/* インクルード	============================================================= */
#include <stm32f4xx.h>

/* 定数定義	============================================================= */
#define USART2_RECV_TIMEOUT_MS	200	// S先輩の勘
#define USART3_RECV_TIMEOUT_MS	200	// S先輩の勘

#define BT_BAUDRATE	9600

/* 関数プロトタイプ宣言	===================================================== */
/* -------------------------------------------------
 * @関数名			:	USART2_Init, USART3_Init
 * @概要				:	USART2, USART3を初期化する
 * @引数-baud		:	ボーレートを設定する
 *　          -autoforward		0	: USART2から返信する
 *　          					1	: USART3から返信する
 *　          					ほか	: 返信しない
 * @戻り値			:	なし
 * ---------------------------------------------- */
void USART2_Init(int baud, int autoforward);
void USART3_Init(int baud, int autoforward);

/* -------------------------------------------------
 * @関数名	:	USART2_RecvByte, USART3_RecvByte
 * @概要		:	USART2, USART3から1[Byte]の情報を受け取る
 * @引数		:	なし
 * @戻り値	:	受信したデータ
 * ---------------------------------------------- */
int USART2_RecvByte(void);
int	USART3_RecvByte(void);

/* -------------------------------------------------
 * @関数名	:	USART2_RecvString, USART3_RecvString
 * @概要		:	USART2, USART3からmax[Byte]受け取り、
 * 				文字列として解釈する
 * @引数-buf	:	受け取った文字列の格納先
 *　          -max	:	文字列の長さ[Byte]
 * @戻り値	:	エラー
 * ---------------------------------------------- */
int	USART2_RecvString(char *buf, int max);
int	USART3_RecvString(char *buf, int max);

/* -------------------------------------------------
 * @関数名		:	USART2_SendByte, USART3_SendByte
 * @概要			:	USART2, USART3から1[Byte]送信する
 * @引数-byte	:	送信する1[Byte]文字
 * @戻り値		:	なし
 * ---------------------------------------------- */
void USART2_SendByte(u8 byte);
void USART3_SendByte(u8 byte);

/* -------------------------------------------------
 * @関数名	:	USART2_SendString, USART3_SendString
 * @概要		:	USART2, USART3から文字列を送信する
 * @引数-buf	:	送信する文字列
 * @戻り値	:	なし
 * ---------------------------------------------- */
void USART2_SendString(char *str);
void USART3_SendString(char *str);

#endif /* __USART_H__ */
