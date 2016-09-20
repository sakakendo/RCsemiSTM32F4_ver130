/***************************************************************************
 *	@ファイル名		:	07_RotaryENC.c
 *	@概要		:	ロータリーエンコーダのカウント数を読み取り，LCDに表示する．
 *					使用するときに必要な処理はコメントの先頭に**がついていますので，使用の際は
 *					必ず記入するようにしてください．
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __07_ENC__

#include <stm32f4xx.h>
#include "timer.h"
#include "lcd.h"
#include "xprintf.h"
#include "rotary_encoder.h"	// **これが必要

int main(void)
{
	int enc[4] = {0};
	int i;

	SystemCoreClockUpdate();	// **システムクロックを初期化する
	TIM7_CMT_Init();	// **ENC2,3を使用するために初期化する

	/* LCDの初期化 */
	xdev_out(LCD_DrawChar);	// 1文字表示する関数を登録しておくことで， xprintf関数での表示が可能になる．
	LCD_Init();
	LCD_Clear();
	LCD_LocateChar(0, 0);

	/* ロータリーエンコーダの初期化 */
	ENC0_Init();	// **ENC0の初期化をする
	ENC1_Init();	// **ENC1の初期化をする
	ENC2_Init();	// **ENC2の初期化をする
	ENC3_Init();	// **ENC3の初期化をする

	xprintf("[Sample No.6]\n");

	while(1)
	{
		LCD_LocateChar(0, 1);

		for(i = 0; i < 4; i++)
		{
			/* こうすることで，ENC_CheckCNTのオーバーフローを防止できる
			 * しかし，割り込みが入るとカウントを取り損ねる可能性もある */
			enc[i] += ENC_CheckCNT(i);
			ENC_ClearCNT(i);

			xprintf("ENC%d:%6d\n", i, enc[i]);
		}
	}
}

#endif /* __07_ENC__ */
