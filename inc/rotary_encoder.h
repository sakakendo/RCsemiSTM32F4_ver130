/***************************************************************************
 *	@ファイル名		:	rotary_encoder.h
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

#ifndef __ROTARY_ENCODER_H__
#define __ROTARY_ENCODER_H__

/* インクルード	============================================================= */
#include <stm32f4xx.h>

/* 定数定義	============================================================= */
/* ロータリーエンコーダが使用するタイマ */
#define ENC0_TIM	TIM2
#define ENC1_TIM	TIM3

/* ロータリーエンコーダが使用するポートなど */
#define ENC0_A_PORT	GPIOA
#define ENC0_A_PIN	GPIO_Pin_15
#define ENC0_B_PORT	GPIOB
#define ENC0_B_PIN	GPIO_Pin_3
#define ENC1_A_PORT	GPIOB
#define ENC1_A_PIN	GPIO_Pin_4
#define ENC1_B_PORT	GPIOB
#define ENC1_B_PIN	GPIO_Pin_5
#define ENC2_A_PORT	GPIOB
#define ENC2_A_PIN	GPIO_Pin_7
#define ENC2_B_PORT	GPIOB
#define ENC2_B_PIN	GPIO_Pin_8
#define ENC3_A_PORT	GPIOC
#define ENC3_A_PIN	GPIO_Pin_8
#define ENC3_B_PORT	GPIOC
#define ENC3_B_PIN	GPIO_Pin_9

/* Bit Banding */
#define ENC2_A_IDR_ADDR_BB	0x4240821c
#define ENC2_B_IDR_ADDR_BB	0x42408220
#define ENC3_A_IDR_ADDR_BB	0x42410220
#define ENC3_B_IDR_ADDR_BB	0x42410224

/* マクロ定義	============================================================= */
/* -------------------------------------------------
 * @マクロ名	:	ENCm_CheckCNT
 * @概要		:	ロータリーエンコーダの値を読み取る
 * @引数		:	なし
 * @戻り値	:	-2^16 ~ 2^16-1の範囲でのカウンタの値
 * @留意点	:	エンコーダの値は16bitを超えるとオーバーフローする
 * 				累積を計算しつつ値をクリアするなど対策すること
 *				<例>enc += ENC_ReadCNT();
 * 				    ENC_ClearCNT(ENC0_CH);
 * ---------------------------------------------- */
#define ENC0_CheckCNT()	((signed short)ENC0_TIM->CNT)
#define ENC1_CheckCNT()	((signed short)ENC1_TIM->CNT)
#define ENC2_CheckCNT()	((signed short)gENC2_CNT)
#define ENC3_CheckCNT()	((signed short)gENC3_CNT)

/* -------------------------------------------------
 * @マクロ名	:	ENC_CheckCNT
 * @概要		:	ロータリーエンコーダの値を読み取る
 * @引数-ch	:	読み取るロータリーエンコーダ
 * @戻り値	:	-2^16 ~ 2^16-1の範囲でのカウンタの値
 * @留意点	:	ENCn_ReadCNTと同様．
 * 				存在しないチャンネルを選択した場合0を返す
 * ---------------------------------------------- */
#define ENC_CheckCNT(ch)	((ch) == 0 ? ENC0_CheckCNT() : \
						 	 (ch) == 1 ? ENC1_CheckCNT() : \
						 	 (ch) == 2 ? ENC2_CheckCNT() : \
						 	 (ch) == 3 ? ENC3_CheckCNT() : 0)

/* -------------------------------------------------
 * @マクロ名	:	ENCn_ClearCNT
 * @概要		:	ロータリーエンコーダのカウントの値をリセットする
 * @引数		:	なし
 * @戻り値	:	なし
 * @留意点	:	ENC_ReadCNT関数と同様
 * ---------------------------------------------- */
#define ENC0_ClearCNT()	(ENC0_TIM->CNT = 0)
#define ENC1_ClearCNT()	(ENC1_TIM->CNT = 0)
#define ENC2_ClearCNT()	(gENC2_CNT = 0)
#define ENC3_ClearCNT()	(gENC3_CNT = 0)

/* -------------------------------------------------
 * @マクロ名	:	ENC_ClearCNT
 * @概要		:	ロータリーエンコーダのカウントの値をリセットする
 * @引数-ch	:	クリアするロータリーエンコーダ
 * @戻り値	:	なし
 * @留意点	:	ENCn_ClearCNT関数と同様．
 * 				存在しないチャンネルを選んだ場合何もしない
 * ---------------------------------------------- */
#define ENC_ClearCNT(ch)	((ch) == 0 ? ENC0_ClearCNT() : \
					  	 	 (ch) == 1 ? ENC1_ClearCNT() : \
					  	 	 (ch) == 2 ? ENC2_ClearCNT() : \
					  	 	 (ch) == 3 ? ENC3_ClearCNT() : 0)

/* 変数プロトタイプ宣言	===================================================== */
extern signed short gENC2_CNT, gENC3_CNT;

/* 関数プロトタイプ宣言	===================================================== */
/* -------------------------------------------------
 * @関数名	:	ENCn_Init
 * @概要		:	ロータリーエンコーダの初期化をする
 * @引数		:	なし
 * @戻り値	:	なし
 * ---------------------------------------------- */
void ENC0_Init(void);
void ENC1_Init(void);
void ENC2_Init(void);
void ENC3_Init(void);

#endif /* __ROTARY_ENCODER_H__ */
