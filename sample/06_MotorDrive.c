/***************************************************************************
 *	@ファイル名		:	06_MotorDrive.c
 *	@概要		:	DIGITAL-IOからモータ駆動のためにPWM信号を出力します．
 *					使用するときに必要な処理はコメントの先頭に**がついていますので，使用の際は
 *					必ず記入するようにしてください．
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include "sample.h"

#ifdef __06_MD__

#include <stm32f4xx.h>
#include "motherboard.h"
#include "timer.h"
#include "digitalIO.h"	// **これが必要
#include "motor.h"		// **これが必要

int main(void)
{
	int i;
	int dir = 1;

	SystemCoreClockUpdate();	// **システムクロックを初期化する
	TIM7_CMT_Init();	// **PWMを生成するために必要

	DIO0_Init(0xFF, DIO_MODE_OUT);	// **モータポートとして使用するピンを出力に設定しておく
	DIO1_Init(0xFF, DIO_MODE_OUT);	// **モータポートとして使用するピンを出力に設定しておく
	DIO2_Init(0xFF, DIO_MODE_OUT);	// **モータポートとして使用するピンを出力に設定しておく

	MotorDriver_Init(0x0CCC);	// **12bitでモータポートの有効・無効を設定する
								//   この場合はそれぞれのポートの下位２つが無効になる

	MB_RotarySW_Init();

	while(1)
	{
		if(MB_PushSW_IsPushed())	dir = -1;
		else						dir =  1;

		for (i = 0; i < 12; i++)
		{
			if(i%2)	Motor_Drive(i, dir * MB_RotarySW_Check()*6);
			else	Motor_Drive(i, dir * MB_RotarySW_Check()*6);
		}

		/* 無効にしたDigital-IOは別の機能として使用できる */
		DIO_OutputPin(0, 0, 1);
		DIO_OutputPin(0, 1, 1);
		DIO_OutputPin(0, 2, 1);
		DIO_OutputPin(0, 3, 1);
		DIO_OutputPin(1, 0, 1);
		DIO_OutputPin(1, 1, 1);
		DIO_OutputPin(1, 2, 1);
		DIO_OutputPin(1, 3, 1);
		DIO_OutputPin(2, 0, 1);
		DIO_OutputPin(2, 1, 1);
		DIO_OutputPin(2, 2, 1);
		DIO_OutputPin(2, 3, 1);
	}
}

#endif /* __06_MD__ */
