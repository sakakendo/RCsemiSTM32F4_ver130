/***************************************************************************
 *	@ファイル名		:	02_PSpad.c
 *	@概要		:	PSコントローラからボタン，スティックの情報を受け取り，LCDに表示します．
 *					USART2がBluetoothで，USART3が電話線であり，それぞれプログラムの書き方
 *					が異なるので注意してください．
 *					使用するときに必要な処理はコメントの先頭に**がついていますので，使用の際は
 *					必ず記入するようにしてください．
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __02_PSPAD__

#include <stm32f4xx.h>
#include "lcd.h"
#include "xprintf.h"
#include "timer.h"	// **これが必要
#include "usart.h"	// **これが必要
#include "pspad.h"	// **これが必要

// 90msぐらいが最適
#define LCD_REDRAW_CYCLE_MS	90

/* どのポートにPSコントローラを繋ぐかを
 * コメントアウトにて切り替えてください */
#define PSPAD_BT	1	// Bluetooth
//#define PSPAD_RJ12	1	// 電話線

int main(void)
{
	int time0 = 0;

	psdata_format_t psdata;	// **コントローラの情報を格納する構造体

	SystemCoreClockUpdate();	// **システムクロックを初期化する

	TIM7_CMT_Init();	// **タイムアウトするために必要

	/* LCDの初期化 */
	xdev_out(LCD_DrawChar);
	LCD_Init();
	LCD_Clear();
	LCD_LocateChar(0, 0);

	xprintf("Now connecting...\n");

#if defined(PSPAD_BT)
	USART2_Init(BT_BAUDRATE, -1);	// **自動返信なしで初期化
	USART2_BDSlave_Init(0);			// **コントローラがコネクトするまでループする
#elif defined(PSPAD_RJ12)
	USART3_Init(BT_BAUDRATE, -1);	// **自動返信なしで初期化
	USART3_BDSlave_Init(0);			// **コントローラがコネクトするまでループする
#endif

	while(1)
	{
#if		defined(PSPAD_BT)
		USART2_PSdata_Recv(&psdata);	// **コントローラの情報を受け取る
#elif	defined(PSPAD_RJ12)
		USART3_PSdata_Recv(&psdata);	// **コントローラの情報を受け取る
#endif

		/* 再描画の処理 */
		if(SystemTimer_ms_Check() - time0 >= LCD_REDRAW_CYCLE_MS)
		{
			time0 = SystemTimer_ms_Check();
			LCD_Clear();
		}

		/* 以下のようにpsdata_format_t型の変数をpsdataとしたとき，
		 * 各ボタンなどの情報はPS_から始まるマクロで情報を受け取れる． */

		LCD_LocateChar(0, 0);

		xprintf("[STICK_L/STICK_R]\nX:%2d/Y:%2d\nX:%2d/Y:%2d\n", PS_STICK_LX(psdata), PS_STICK_LY(psdata)
												  	  	  	   , PS_STICK_RX(psdata), PS_STICK_RY(psdata));

		xprintf("[The Button]\n");
		if(PS_B_R1		(psdata))	xprintf("R1\n");
		if(PS_B_R2		(psdata))	xprintf("R2\n");
		if(PS_B_L1		(psdata))	xprintf("L1\n");
		if(PS_B_L2		(psdata))	xprintf("L2\n");
		if(PS_B_TRIANGLE(psdata))	xprintf("TRIANGLE\n");
		if(PS_B_CIRCLE	(psdata))	xprintf("CIRCLE\n");
		if(PS_B_CROSS	(psdata))	xprintf("CROSS\n");
		if(PS_B_SQUARE	(psdata))	xprintf("SQUARE\n");
		if(PS_B_START	(psdata))	xprintf("START\n");
		if(PS_B_SELECT	(psdata))	xprintf("SELECT\n");
		if(PS_B_ARROW_U	(psdata))	xprintf("ARROW_U\n");
		if(PS_B_ARROW_R	(psdata))	xprintf("ARROW_R\n");
		if(PS_B_ARROW_D	(psdata))	xprintf("ARROW_D\n");
		if(PS_B_ARROW_L	(psdata))	xprintf("ARROW_L\n");
		if(PS_B_STICK_R (psdata))	xprintf("STICK_R\n");
		if(PS_B_STICK_L (psdata))	xprintf("STICK_L\n");
	}
}

#endif /* __02_PSPAD__ */
