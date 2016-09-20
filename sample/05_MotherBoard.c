/***************************************************************************
 *	@ファイル名		:	05_MotherBoard.c
 *	@概要		:	MB上のLED，プッシュスイッチ，ロータリースイッチを制御します．
 *					プッシュスイッチ，ロータリースイッチの状態はLCDに表示しています．
 *					使用するときに必要な処理はコメントの先頭に**がついていますので，使用の際は
 *					必ず記入するようにしてください．
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __05_MB__

#include <stm32f4xx.h>
#include "lcd.h"
#include "xprintf.h"
#include "timer.h"
#include "motherboard.h"	// **これが必要

// 90msぐらいが最適
#define LCD_REDRAW_CYCLE_MS	90

int main(void)
{
	int time0 = 0;

	SystemCoreClockUpdate();	// **システムクロックを初期化する
	TIM7_CMT_Init();

	/* LCDの初期化 */
	xdev_out(LCD_DrawChar);	// 1文字表示する関数を登録しておくことで， xprintf関数での表示が可能になる．
	LCD_Init();
	LCD_Clear();

	/* MB機能の初期化 */
	MB_LED_Init();		// **LEDを使うときこれが必要
	MB_PushSW_Init();	// **プッシュスイッチを使うときこれが必要
	MB_RotarySW_Init();	// **ロータリースイッチを使うときこれが必要

	/* LED */
	MB_LED_TurnOn(0);
	MB_LED_TurnOff(1);

	while(1)
	{
		LCD_LocateChar(0, 0);

		/* 再描画の処理 */
		if(SystemTimer_ms_Check() - time0 >= LCD_REDRAW_CYCLE_MS)
		{
			time0 = SystemTimer_ms_Check();
			LCD_Clear();
		}

		/* LED */
		MB_LED_Toggle(0);
		MB_LED_Toggle(1);

		/* PushSW */
		xprintf("PushSW : ");
		if(MB_PushSW_IsPushed())	xprintf("Pushed\n");
		else						xprintf("Not Pushed\n");

		/* RotarySW */
		xprintf("RotarySW : 0x%x\n", MB_RotarySW_Check());

		delay_ms(100);
	}
}

#endif /* __05_MB__ */
