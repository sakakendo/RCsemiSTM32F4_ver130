/***************************************************************************
 *	@ファイル名		:	03_ADC.c
 *	@概要		:	ANALOG-INに印加された電圧を読み取り，LCDに表示します．
 *					使用するときに必要な処理はコメントの先頭に**がついていますので，使用の際は
 *					必ず記入するようにしてください．
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __03_ADC__

#include <stm32f4xx.h>
#include "lcd.h"
#include "timer.h"
#include "xprintf.h"
#include "adc.h"	// **これが必要

/* どのモードでADCをするかを
 * コメントアウトで切り替えてください */
#define ADC_MODE_SIGNLECONV	1	// シングルモード
//#define ADC_MODE_CONTSCAN	1	// 連続スキャンモード，DMA(Direct Memory Access)で読み取る

int main(void)
{
	SystemCoreClockUpdate();	// **システムクロックを初期化する
	TIM7_CMT_Init();

	int i;

	/* LCDの初期化 */
	xdev_out(LCD_DrawChar);
	LCD_Init();
	LCD_Clear();
	LCD_LocateChar(0, 0);

	/* ADCの初期化 */
#if defined(ADC_MODE_SIGNLECONV)
	ADC_Single_Init();	// **ADCをシングルモードで初期化する
#elif defined(ADC_MODE_CONTSCAN)
	ADC_ContScan_Init();	// **ADCを連続スキャンモードで初期化する
#endif

	xprintf("[Sample No.3]\n");

	while(1)
	{
		LCD_LocateChar(0, 0);

		for(i = 0; i < 8; i++)
		{
			if(i%2 == 0)	xprintf("\n");
#if 	defined(ADC_MODE_SIGNLECONV)
			xprintf("%6d ", ADC_Single_Read(i));
#elif	defined(ADC_MODE_CONTSCAN)
			xprintf("%6d ", ADC_ContScan_Read(i));
#endif
		}
	}
}

#endif /* __02_ADC__ */
