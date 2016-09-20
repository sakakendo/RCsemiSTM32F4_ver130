/***************************************************************************
 *	@ファイル名		:	pspad.c
 *	@概要		:	USART3(電話線),USART2(Bluetooth)におけるPSコントローラとの通信を
 *					提供する．
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "usart.h"
#include "pspad.h"
#include "timer.h"

/* -------------------------------------------------
 * @関数名		:	Coincidence_Check
 * @概要			:	str1の先頭からnum文字をstr2と比較する
 * @引数	-str1	:	被比較対象文字列
 * 		-str2	:	比較文字列
 * 		-num	:	str1の先頭から比較する文字数
 * @戻り値		:	一致時に1をそれ以外は0を返す
   ---------------------------------------------- */
static int Coincidence_Check(const char *str1, const char *str2, int num)
{
	int i;
	for(i = 0; i < num; i++)
		if (*str1++ != *str2++)	return 0;
	return 1;
}

/* -------------------------------------------------
 * @関数名		:	PS_CheckSum
 * @概要			:	PSコントローラからの受信チェックサムを調査する
 * @引数-psdata	:	PSコントローラから受け取ったデータ
 * @戻り値		:	チェックサムが真なら1、偽ならば0を返す
   ---------------------------------------------- */
static int PSdata_CheckSum(psdata_format_t *psdata)
{
	u8 sum = 0;
	int i;
	for(i = 0; i < 6; i++)	sum += psdata->bytes[i];
	if(psdata->bytes[6]-1 == sum)	return 1;
	else							return 0;
}

/* -------------------------------------------------
 * @関数名		:	USART2_BDMaster_Init
 * @概要			:	USART2(Bluetooth)との通信で
 * 					自分をマスターとして初期化
 * @引数-command	:	初期化時に自動返信する文字列
 * @戻り値		:	なし
 * ---------------------------------------------- */
void USART2_BDMaster_Init(char *command)
{
	char buff[128];
	USART2_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "OK", 2))
	{
		USART2_RecvString(buff, 128);
	}
	if(command)
	{
		USART2_SendString(command);
		USART2_SendString("\r\n");
	}
	USART2_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "CONNECT", 7))
	{//Slaveとの接続が完了するまで待機。
		USART2_RecvString(buff, 128);
	}
}

/* -------------------------------------------------
 * @関数名		:	USART3_BDMaster_Init
 * @概要			:	USART3(電話線)との通信で
 * 					自分をマスターとして初期化
 * @引数-command	:	初期化時に自動返信する文字列
 * @戻り値		:	なし
   ---------------------------------------------- */
void USART3_BDMaster_Init(char *command)
{
	char buff[128];
	USART3_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "OK", 2))
	{
		USART3_RecvString(buff, 128);
	}
	if(command)
	{
		USART3_SendString(command);
		USART3_SendString("\r\n");
	}
	USART3_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "CONNECT", 7))
	{//Slaveとの接続が完了するまで待機。
		USART3_RecvString(buff,128);
	}
}

/* -------------------------------------------------
 * @関数名		:	USART2_BDSlave_Init
 * @概要			:	USART2(Bluetooth)との通信で
 * 					自分をスレーブとして初期化
 * @引数-command	:	初期化時に自動返信する文字列
 * @戻り値		:	なし
 * ---------------------------------------------- */
void USART2_BDSlave_Init(char *command)
{
	char buff[128];
	USART2_RecvString(buff, 128); //"OK"を受けたはず
	while(!Coincidence_Check(buff, "OK", 2))
	{
		USART2_RecvString(buff, 128);
	}
	if(command)
	{
		USART2_SendString(command);
		USART2_SendString("\r\n");
	}
	USART2_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "CONNECT", 7))
	{//Masterとの接続が完了するまで待機。
		USART2_RecvString(buff, 128);
	}
}

/* -------------------------------------------------
 * @関数名		:	USART3_BDSlave_Init
 * @概要			:	USART3(電話線)との通信で
 * 					自分をスレーブとして初期化
 * @引数-command	:	初期化時に自動返信する文字列
 * @戻り値		:	なし
   ---------------------------------------------- */
void USART3_BDSlave_Init(char *command)
{
	char buff[128];
	USART3_RecvString(buff, 128); //"OK"を受けたはず
	while(!Coincidence_Check(buff, "OK", 2))
	{
		USART3_RecvString(buff, 128);
	}
	if(command)
	{
		USART3_SendString(command);
		USART3_SendString("\r\n");
	}
	USART3_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "CONNECT", 7))
	{//Masterとの接続が完了するまで待機。
		USART3_RecvString(buff, 128);
	}
}

/* -------------------------------------------------
 * @関数名	:	USART2_PSpacket_Recv
 * @概要		:	USART2(Bluetooth)から
 * 				PSコントローラのパケット(7Byte)を受け取る
 * @引数-buf	:	受け取った情報を格納する変数
 * @戻り値	:	情報が受取れれば7を、そうでなければ-1を返す
 * ---------------------------------------------- */
static int USART2_PSpacket_Recv(u8 buf[])
{
	int data, time0;
	int i;

	/* 理由は不明だがdo-while文は利用できなかった */
	data = USART2_RecvByte();
	if(data == -1)	return -1;

	time0 = SystemTimer_ms_Check();
	/* チェックサムのデータを読み取るまでループ */
	while((data&1) == 0)
	{
		data = USART2_RecvByte();
		if(data == -1)	return -1;
		if(SystemTimer_ms_Check() - time0 > PS_RECV_TIMEOUT_MS)	return -1;
	}

	for(i = 0; i < 7; i++)
	{
		buf[i] = USART2_RecvByte();
		if(buf[i] == -1)	return i;
	}
	return i;
}

/* -------------------------------------------------
 * @関数名	:	USART3_PSpacket_Recv
 * @概要		:	USART3(電話線)から
 * 				PSコントローラのパケット(7Byte)を受け取る
 * @引数-buf	:	受け取った情報を格納する変数
 * @戻り値	:	情報が受け取れれば7を、そうでなければ-1を返す
   ---------------------------------------------- */
static int USART3_PSpacket_Recv(u8 buf[])
{
	int data, time0;
	int i;

	/* 理由は不明だがdo-while文は利用できなかった */
	data = USART3_RecvByte();
	if(data == -1)	return -1;

	time0 = SystemTimer_ms_Check();
	/* チェックサムのデータを読み取るまでループ */
	while((data&1) == 0)
	{
		data = USART3_RecvByte();
		if(data == -1)	return -1;
		if(SystemTimer_ms_Check() - time0 > PS_RECV_TIMEOUT_MS)	return -1;
	}

	for(i = 0; i < 7; i++)
	{
		buf[i] = USART3_RecvByte();
		if(buf[i] == -1)	return i;
	}
	return i;
}

/* -------------------------------------------------
 * @関数名		:	USART2_PSdata_Recv
 * @概要			:	USART2(電話線)から
 * 					PSコントローラのデータを受信する．
 * @引数-psdata	:	コントローラデータ格納先の変数
 * @戻り値		:	なし
 * ---------------------------------------------- */
void USART2_PSdata_Recv(psdata_format_t *psdata)
{
	int i;
	static int mode;
	int nBytes, sumchk = -1;
	nBytes = USART2_PSpacket_Recv(psdata->bytes);
	if(nBytes == 7)	sumchk = PSdata_CheckSum(psdata);
	if(sumchk == 1)
	{
		mode = psdata->name.Mode;
		psdata->name.Error = 0;
	}
	else
	{
		psdata->bytes[0] = psdata->bytes[1] = 0;
		for(i = 2; i < 7; i++)	psdata->bytes[i] = 0x80;
		psdata->name.LStick_X = psdata->name.LStick_Y =
		psdata->name.RStick_X = psdata->name.RStick_Y = 7;
		psdata->name.Mode = mode;
		psdata->name.Error = 1;
	}
}

/* -------------------------------------------------
 * @関数名		:	USART3_PSdata_Recv
 * @概要			:	USART3(電話線)から
 * 					PSコントローラのデータを受信する．
 * @引数-psdata	:	コントローラデータ格納先の変数
 * @戻り値		:	なし
 * ---------------------------------------------- */
void USART3_PSdata_Recv(psdata_format_t *psdata)
{
	int i;
	static int mode;
	int nBytes, sumchk = -1;
	nBytes = USART3_PSpacket_Recv(psdata->bytes);
	if(nBytes == 7)	sumchk = PSdata_CheckSum(psdata);
	if(sumchk == 1)
	{
		mode = psdata->name.Mode;
		psdata->name.Error = 0;
	}
	else
	{
		psdata->bytes[0] = psdata->bytes[1] = 0;
		for(i = 2; i < 7; i++)	psdata->bytes[i] = 0x80;
		psdata->name.LStick_X = psdata->name.LStick_Y =
		psdata->name.RStick_X = psdata->name.RStick_Y = 7;
		psdata->name.Mode = mode;
		psdata->name.Error = 1;
	}
}
