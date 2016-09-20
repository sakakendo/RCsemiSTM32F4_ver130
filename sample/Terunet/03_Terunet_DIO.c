/***************************************************************************
 *	@ファイル名		:	08_RS485_MD.c
 *	@概要		:	LTC485を使用してLPCマイコンとシリアル通信を行い，モータ駆動を行うためにPWM
 *					信号を出力します．
 *					使用するときに必要な処理はコメントの先頭に**がついていますので，使用の際は
 *					必ず記入するようにしてください．
 *					いくつめのLPCかについてはLPC_NO_1とLPC_NO_2のみrs485_master.hで定義
 *					してあるのでLPCを3つ以上接続して使用する場合は自分で定義してください．
 *	@バージョン		:	1.0.0
 *	@開発者		:	太田那菜
 *	@使用環境	:	STM32F4DISCOVERY, LPC1114FN28-102, LTC485, MB_Ver2, CooCox CoIDE
 **************************************************************************/
#include "sample.h"

#ifdef __08_RS485_MD__

#include <stm32f4xx.h>
#include "lcd.h"
#include "xprintf.h"
#include "motherboard.h"
#include "timer.h"			// **これが必要，タイムアウト処理に用いる．
#include "terunet.h"		// **これが必要，データを送受信するのに必要
#include "terunet_motorDriver.h"	// **これが必要，モータを駆動する関数を使うため必要

#define LPC_NO_1 0x01
#define LPC_NO_2 0x02

int main(void)
{
	int dir = 1;
	int i;
	u8 recvData;

	SystemCoreClockUpdate();	// **システムクロックを初期化する
	TIM7_CMT_Init();	// delayを使用するために初期化する

	/* LCDの初期化 */
	xdev_out(LCD_DrawChar);	// 1文字表示する関数を登録しておくことで， xprintf関数での表示が可能になる．
	LCD_Init();
	LCD_Clear();
	LCD_LocateChar(0, 0);
	xprintf("[Sample No.8]\n");

	RS485_Init(RS485_BAUDRATE);	// **RS485の初期化

	MB_RotarySW_Init();
	MB_PushSW_Init();

	while(1)
	{
		if(MB_PushSW_IsPushed())	dir = -1;
		else						dir =  1;

		RS485_Motor_Drive(LPC_NO_1, 0, dir *  MB_RotarySW_Check()*1, &recvData);	//1つ目のLPCのポート0に出力
		RS485_Motor_Drive(LPC_NO_1, 1, dir *  MB_RotarySW_Check()*2, &recvData);	//1つ目のLPCのポート1に出力
		RS485_Motor_Drive(LPC_NO_1, 2, dir *  MB_RotarySW_Check()*3, &recvData);	//1つ目のLPCのポート2に出力
		RS485_Motor_Drive(LPC_NO_1, 3, dir *  MB_RotarySW_Check()*4, &recvData);	//1つ目のLPCのポート3に出力
		RS485_Motor_Drive(LPC_NO_1, 4, dir *  MB_RotarySW_Check()*5, &recvData);	//1つ目のLPCのポート4に出力
		RS485_Motor_Drive(LPC_NO_1, 5, dir *  MB_RotarySW_Check()*6, &recvData);	//1つ目のLPCのポート5に出力
		RS485_Motor_Drive(LPC_NO_1, 6, dir * -MB_RotarySW_Check()*6, &recvData);	//1つ目のLPCのポート6に出力
		RS485_Motor_Drive(LPC_NO_1, 7, RS485_BRAKEVALUE, &recvData);				//1つ目のLPCのポート7に出力

		for(i = 0; i < 8; i++)	RS485_Motor_Drive(LPC_NO_2, i, dir * MB_RotarySW_Check()*6, &recvData);	//2つ目のLPCのポートすべてに出力
	}
}

#endif /* __08_RS485_MD__ */
