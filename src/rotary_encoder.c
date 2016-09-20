/***************************************************************************
 *	@ファイル名		:	rotary_encoder.c
 *	@概要		:	ロータリーエンコーダポートの初期化と，読み取りを提供する．
 *					ポートはENC0-3があり，使用するタイマ，GPIOは以下のとおり，
 *					ENC0	:TIM2	A:PA15 / B:PB3
 *					ENC1	:TIM3	A:PB4  / B:PB5
 *					ENC2	:TIM4	A:PB7  / B:PB8
 *					ENC3	:TIM8	A:PC8  / B:PC9
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "rotary_encoder.h"

signed short gENC2_CNT = 0, gENC3_CNT = 0;

/* -------------------------------------------------
 * @関数名	:	ENCn_Init
 * @概要		:	ロータリーエンコーダの初期化をする
 * @引数		:	なし
 * @戻り値	:	なし
 * ---------------------------------------------- */
void ENC0_Init(void)
{
	/* クロックを供給 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* GPIOの初期化 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// プルアップ抵抗は外部で接続済み
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* GPIOピンをタイマとして利用する設定 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3 , GPIO_AF_TIM2);

	/* タイマの設定 */
	TIM_DeInit(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period 		= 0xffff;	// 最大値
	TIM_TimeBaseStructure.TIM_Prescaler 	= 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* ロータリーエンコーダ設定 */
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,
							   TIM_ICPolarity_Rising,
							   TIM_ICPolarity_Rising);
	// タイマを有効化
	TIM_Cmd(TIM2, ENABLE);
}

void ENC1_Init(void)
{
	/* クロックを供給 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* GPIOの初期化 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// プルアップ抵抗は外部で接続済み
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* GPIOピンをタイマとして利用する設定 */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);

	/* タイマの設定 */
	TIM_DeInit(TIM3);	// 必要ないかもしれない
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period 		= 0xffff;	// 最大値
	TIM_TimeBaseStructure.TIM_Prescaler 	= 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* ロータリーエンコーダ設定 */
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,
							   TIM_ICPolarity_Rising,
							   TIM_ICPolarity_Rising);
	// タイマを有効化
	TIM_Cmd(TIM3, ENABLE);
}

void ENC2_Init(void)
{
	/* クロックを供給 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* GPIOの初期化 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// プルアップ抵抗は外部で接続済み
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	gENC2_CNT = 0;
}

void ENC3_Init(void)
{
	/* クロックを供給 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* GPIOの初期化 */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// プルアップ抵抗は外部で接続済み
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	gENC3_CNT = 0;
}
