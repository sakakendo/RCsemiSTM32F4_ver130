/***************************************************************************
 *	@ファイル名		:	motherboard.c
 *	@概要		:	MB上のLED，プッシュスイッチ，ロータリースイッチの機能を提供します．
 *					以下に，各要素のピン配置を示します．
 *					LED			0:PA8, 1:PB14
 *					PushSW		0:PE7
 *					RotarySW	0:PE2, 1:PE4, 2:PE5, 3:PE6
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "motherboard.h"

/* -------------------------------------------------
 * @関数名	:	MB_LED_Init
 * @概要		:	MB上LEDに接続されているGPIO(PA8, PB14)を
 * 				初期化します．
 * @引数		:	なし
 * @戻り値	:	なし
 * ---------------------------------------------- */
void MB_LED_Init(void)
{
	/* クロック供給 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* GPIO設定 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin	  = GPIO_Pin_14;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/* -------------------------------------------------
 * @関数名	:	MB_LED_TurnOff
 * @概要		:	指定のLEDを消灯します．
 * @引数-num	:	LEDの番号、0, 1
 * @戻り値	:	なし
 * ---------------------------------------------- */
void MB_LED_TurnOff(int num)
{
	if     (num == 0) GPIOA->BSRRH = GPIO_Pin_8;
	else if(num == 1) GPIOB->BSRRH = GPIO_Pin_14;
}

/* -------------------------------------------------
 * @関数名	:	MB_LED_TurnOn
 * @概要		:	指定のLEDを点灯します．
 * @引数-num	:	LEDの番号、0, 1
 * @戻り値	:	なし
 * ---------------------------------------------- */
void MB_LED_TurnOn(int num)
{
	if     (num == 0) GPIOA->BSRRL = GPIO_Pin_8;
	else if(num == 1) GPIOB->BSRRL = GPIO_Pin_14;
}

/* -------------------------------------------------
 * @関数名	:	MB_LED_Toggle
 * @概要		:	指定のLEDを前回と違う状態にします．
 * @引数-num	:	LEDの番号、0, 1
 * @戻り値	:	なし
 * ---------------------------------------------- */
void MB_LED_Toggle(int num)
{
	if     (num == 0) GPIOA->ODR ^= GPIO_Pin_8;
	else if(num == 1) GPIOB->ODR ^= GPIO_Pin_14;
}

/* -------------------------------------------------
 * @関数名	:	MB_PushSW_Init
 * @概要		:	プッシュスイッチに接続されているGPIO(PE7)の
 * 				初期化をします．
 * @引数		:	なし
 * @戻り値	:	なし
 * ---------------------------------------------- */
void MB_PushSW_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/* -------------------------------------------------
 * @関数名	:	MB_PushSW_IsPushed
 * @概要		:	プッシュスイッチが押されたかどうか判定します．
 * @引数		:	なし
 * @戻り値	:	押されたら1, そうでなければ0
 * ---------------------------------------------- */
int MB_PushSW_IsPushed(void)
{
	if(GPIOE->IDR & GPIO_Pin_7)	return 1;
	else						return 0;
}

/* -------------------------------------------------
 * @関数名	:	MB_RotarySW_Init
 * @概要		:	ロータリースイッチに接続されている
 * 				GPIO(PE2, PE4, PE5, PE6)の初期化をします．
 * @引数		:	なし
 * @戻り値	:	なし
 * ---------------------------------------------- */
void MB_RotarySW_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/* -------------------------------------------------
 * @関数名	:	MB_RotarySW_Check
 * @概要		:	ロータリースイッチが示す値(0-15)を判別します．
 * @引数		:	なし
 * @戻り値	:	ロータリースイッチの値(0-15)
 * ---------------------------------------------- */
u8 MB_RotarySW_Check(void)
{
	return (((GPIOE->IDR & GPIO_Pin_2) >> 2) | ((GPIOE->IDR & GPIO_Pin_4) >> 3) |
			((GPIOE->IDR & GPIO_Pin_5) >> 3) | ((GPIOE->IDR & GPIO_Pin_6) >> 3));

}
