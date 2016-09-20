/***************************************************************************
 *	@ファイル名		:	04_DIO.c
 *	@概要		:	DIGITAL-IOxに印加されたHIGH/LOWを読み取り，LCDに表示したり，
 *					DIGITAL-IOxからHIGH/LOWを出力したりします．
 *					使用するときに必要な処理はコメントの先頭に**がついていますので，使用の際は
 *					必ず記入するようにしてください．
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __04_DIO__

#include <stm32f4xx.h>
#include "lcd.h"
#include "timer.h"
#include "xprintf.h"
#include "digitalIO.h"	// **これが必要

int main(void)
{
	SystemCoreClockUpdate();	// **システムクロックを初期化する
	TIM7_CMT_Init();

	u8 d_in;
	int i;

	/* LCDの初期化 */
	xdev_out(LCD_DrawChar);	// 1文字表示する関数を登録しておくことで， xprintf関数での表示が可能になる．
	LCD_Init();
	LCD_Clear();
	LCD_LocateChar(0, 0);

	xprintf("[Sample No.4]\n");

	/* DIGITAL-IOの初期化 */
	DIO0_Init(0xFF, DIO_MODE_OUT);	// **0xFF→0b11111111，つまり，DIO0の8ピンすべてを出力に設定する．
	DIO1_Init(0xFF, DIO_MODE_IN);	// **0xFF→0b11111111，つまり，DIO0の8ピンすべてを入力に設定する．
	DIO2_Init(0xFF, DIO_MODE_OUT);	// **0xFF→0b11111111，つまり，DIO0の8ピンすべてを出力に設定する．

	/* 以下のようなこともできる
	DIO0_Init(0xF0, DIO_MODE_IN);	// **0xF0→0b11110000，つまり，DIO0の上位4ピンを入力に設定する．
	DIO0_Init(0x0F, DIO_MODE_OUT);	// **0x0F→0b00001111，つまり，DIO0の下位4ピンを出力に設定する．
	DIO1_Init(0xF0, DIO_MODE_IN);	// **0xF0→0b11110000，つまり，DIO1の上位4ピンを入力に設定する．
	DIO1_Init(0x0F, DIO_MODE_OUT);	// **0x0F→0b00001111，つまり，DIO1の下位4ピンを出力に設定する．
	DIO2_Init(0xF0, DIO_MODE_IN);	// **0xF0→0b11110000，つまり，DIO2の上位4ピンを入力に設定する．
	DIO2_Init(0x0F, DIO_MODE_OUT);	// **0x0F→0b00001111，つまり，DIO2の下位4ピンを出力に設定する．
	*/

	while(1)
	{
		LCD_LocateChar(0, 1);

		/* ポート0,2から信号を出力する */
		for(i = 0; i < 8; i++)
		{
			DIO_OutputPin(0, i, 1);
			DIO_OutputPin(2, i, 1);
		}

		/* ポート1の各ビットを受け取れる */
		d_in = DIO_CheckPin(1, 0) 	  | (DIO_CheckPin(1, 1)<<1) | (DIO_CheckPin(1, 2)<<2) | (DIO_CheckPin(1, 3)<<3) |
			  (DIO_CheckPin(1, 4)<<4) | (DIO_CheckPin(1, 5)<<5) | (DIO_CheckPin(1, 6)<<6) | (DIO_CheckPin(1, 7)<<7);

		xprintf("\r0x%02x", d_in);
	}
}

#endif /* __04_DIO__ */
