/***************************************************************************
 *	@ファイル名		:	01_LCD.c
 *	@概要		:	MB上にあるLCDの表示テストを行います．
 *					フォントは，tri_S_Font6x8_90.hを使用しております．
 *					使用するときに必要な処理はコメントの先頭に**がついていますので，使用の際は
 *					必ず記入するようにしてください．
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __01_LCD__

#include <stm32f4xx.h>
#include "lcd.h"		// **これが必要
#include "timer.h"		// **これが必要
#include "xprintf.h"	// **これが必要

int main(void)
{
	u8 cnt;

	SystemCoreClockUpdate();	// **システムクロックを初期化する

	TIM7_CMT_Init();	// **LCD_Init内のdelay_msを使用するために必要

	/* LCDの初期化 */
	xdev_out(LCD_DrawChar);	// 1文字表示する関数を登録しておくことで， xprintf関数での表示が可能になる．
	LCD_Init();				// **LCDの初期化
	LCD_Clear();			// **表示をクリアする
	LCD_LocateChar(0, 0);	// 文字を描画する座標を指定する

	for(cnt = 3; cnt > 0; cnt--)
	{
		xprintf("\r%d", cnt);	// \rで文字列を左詰にする．
		delay_ms(1000);
	}

	LCD_Clear();
	LCD_LocateChar(0, 0);

	xprintf("!! Hello World !!\n!! Yes, Kinect !!");	// \nで改行

	while(1)
	{
		cnt &= 0x3F;
		LCD_ScrollPixel(cnt++);	// ピクセル単位で縦にスクロールする
		delay_ms(100);
	}
}

#endif /* __01_LCD__ */
