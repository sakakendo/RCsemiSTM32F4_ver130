/***************************************************************************
 *	@ファイル名		:	digitalIO.h
 *	@概要		:	DIGITAL-IOxポートを用いて，デジタル的な入出力を行います．
 *					以下にマザーボード上に設けられているDIGITAL-IOxのピン配置を示します．
 *
 *					[DIO0]	PE8 , PE9 , PE10, PE11, PE12, PE13, PE14, PE15
 *					[DIO1]	PD3 , PD7 , PD10, PD11, PD12, PD13, PD14, PD15
 *					[DIO2]	PC6 , PC11, PC13, PC14, PC15, PD0 , PD1 , PD2
 *
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#ifndef __DIGITALIO_H__
#define __DIGITALIO_H__

/* インクルード	============================================================= */
#include <stm32f4xx.h>

/* 定数定義	============================================================= */
/*--------------------------------------------------
 * DigitalIO0
 * PE8, PE9, PE10, PE11, PE12, PE13, PE14, PE15
 ------------------------------------------------ */
#define DIO0_0_PORT	GPIOE
#define DIO0_0_PIN	GPIO_Pin_8
#define DIO0_1_PORT GPIOE
#define DIO0_1_PIN	GPIO_Pin_9
#define DIO0_2_PORT	GPIOE
#define DIO0_2_PIN	GPIO_Pin_10
#define DIO0_3_PORT GPIOE
#define DIO0_3_PIN	GPIO_Pin_11
#define DIO0_4_PORT	GPIOE
#define DIO0_4_PIN	GPIO_Pin_12
#define DIO0_5_PORT GPIOE
#define DIO0_5_PIN	GPIO_Pin_13
#define DIO0_6_PORT	GPIOE
#define DIO0_6_PIN	GPIO_Pin_14
#define DIO0_7_PORT GPIOE
#define DIO0_7_PIN	GPIO_Pin_15

/*--------------------------------------------------
 * DigitalIO1
 * PD3, PD7, PD10, PD11, PD12, PD13, PD14, PD15
 ------------------------------------------------ */
#define DIO1_0_PORT	GPIOD
#define DIO1_0_PIN	GPIO_Pin_3
#define DIO1_1_PORT GPIOD
#define DIO1_1_PIN	GPIO_Pin_7
#define DIO1_2_PORT	GPIOD
#define DIO1_2_PIN	GPIO_Pin_10
#define DIO1_3_PORT GPIOD
#define DIO1_3_PIN	GPIO_Pin_11
#define DIO1_4_PORT	GPIOD
#define DIO1_4_PIN	GPIO_Pin_12
#define DIO1_5_PORT GPIOD
#define DIO1_5_PIN	GPIO_Pin_13
#define DIO1_6_PORT	GPIOD
#define DIO1_6_PIN	GPIO_Pin_14
#define DIO1_7_PORT GPIOD
#define DIO1_7_PIN	GPIO_Pin_15

/*--------------------------------------------------
 * DigitalIO2
 * PC6, PC11, PC13, PC14, PC15, PD0, PD1, PD2
 ------------------------------------------------ */
#define DIO2_0_PORT	GPIOC
#define DIO2_0_PIN	GPIO_Pin_6
#define DIO2_1_PORT GPIOC
#define DIO2_1_PIN	GPIO_Pin_11
#define DIO2_2_PORT	GPIOC
#define DIO2_2_PIN	GPIO_Pin_13
#define DIO2_3_PORT GPIOC
#define DIO2_3_PIN	GPIO_Pin_14
#define DIO2_4_PORT	GPIOC
#define DIO2_4_PIN	GPIO_Pin_15
#define DIO2_5_PORT GPIOD
#define DIO2_5_PIN	GPIO_Pin_0
#define DIO2_6_PORT	GPIOD
#define DIO2_6_PIN	GPIO_Pin_1
#define DIO2_7_PORT GPIOD
#define DIO2_7_PIN	GPIO_Pin_2

/* 入出力設定 */
#define DIO_MODE_OUT	0
#define DIO_MODE_IN		1

/* マクロ定義	============================================================= */
/* ------------------------------------------------------------
 * @マクロ名		:	DIO_OutputPin
 * @概要			:	Digital-IOxから "0"(0V) or "1"(3V) を出力します．
 * @引数	-port	:	出力ポートを選択します(0-2)．
 * 		-pin	:	出力ピンを選択します(0-7)．
 * 		-status	:	出力の信号(0, 1)
 * @留意点		:	規定外の超えた引数を選択すると，メモリのどこかの値が
 * 					書き換わることになります．
 * --------------------------------------------------------- */
#define DIO_OutputPin(port, pin, status)	(*((u32*)DIO_ODR_ADDR_BB[port][pin]) = (status))

/* ------------------------------------------------------------
 * @マクロ名		:	DIO_TogglePin
 * @概要			:	直前のDigital-IOxの出力状態を反転させます．
 * @引数-port	:	出力ポートを選択します(0-2)．
 * 	   　   -pin		:	出力ピンを選択します(0-7)．
 * @留意点		:	規定外の超えた引数を選択すると，メモリのどこかの値が
 * 					書き換わることになります．
   --------------------------------------------------------- */
#define DIO_TogglePin(port, pin)	(*((u32*)DIO_ODR_ADDR_BB[port][pin]) ^= 1)

/* ------------------------------------------------------------
 * @マクロ名		:	DIO_CheckPin
 * @概要			:	DigitalIOxが入力した信号を読み取ります．
 * @引数-port	:	入力ポートを選択します(0-2)．
 * 	   　   -pin		:	入力ピンを選択します(0-7)．
 * @留意点		:	規定外の引数を選択すると，メモリのどこかの値が
 * 					書き換わることになります．
   --------------------------------------------------------- */
#define DIO_CheckPin(port, pin)	(*((u32*)DIO_IDR_ADDR_BB[port][pin]))

/* 変数プロトタイプ宣言	===================================================== */
/* GPIOxのODRのビットバンド */
extern const u32 DIO_ODR_ADDR_BB[3][8];

/* GPIOxのIDRのビットバンド */
extern const u32 DIO_IDR_ADDR_BB[3][8];

/* 関数プロトタイプ宣言	===================================================== */
/* ------------------------------------------------------------
 * @関数名		:	DIO0_Init
 * @概要			:	Digital-IO0の初期化をします．
 * @引数-pin		:	設定するピンを8ビットで表し、1にしたビットの設定をします．
 * 	   　   -mode	:	1(DIO_MODE_IN )を設定すると入力として初期化
 * 	   				0(DIO_MODE_OUT)を設定すると出力として初期化
   --------------------------------------------------------- */
void DIO0_Init(u8 pin, int mode);

/* ------------------------------------------------------------
 * @関数名		:	DIO1_Init
 * @概要			:	Digital-IO1の初期化をします．
 * @引数-pin		:	設定するピンを8ビットで表し、1にしたビットの設定をします．
 * 	   　   -mode	:	1(DIO_MODE_IN )を設定すると入力として初期化
 * 	   				0(DIO_MODE_OUT)を設定すると出力として初期化
   --------------------------------------------------------- */
void DIO1_Init(u8 pin, int mode);

/* ------------------------------------------------------------
 * @関数名		:	DIO2_Init
 * @概要			:	Digital-IO2の初期化をします．
 * @引数-pin		:	設定するピンを8ビットで表し、1にしたビットの設定をします．
 * 	   　   -mode	:	1(DIO_MODE_IN )を設定すると入力として初期化
 * 	   				0(DIO_MODE_OUT)を設定すると出力として初期化
   --------------------------------------------------------- */
void DIO2_Init(u8 pin, int mode);

#endif /* __DIGITALIO_H__ */
