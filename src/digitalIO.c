/***************************************************************************
 *	@ファイル名		:	digitalIO.c
 *	@概要		:	DIGITAL-IOxポートを用いて，デジタル的な入出力を行います．
 *					以下にマザーボード上に設けられているDIGITAL-IOxのピン配置を示しておきます．
 *
 *					[DIO0]	PE8 , PE9 , PE10, PE11, PE12, PE13, PE14, PE15
 *					[DIO1]	PD3 , PD7 , PD10, PD11, PD12, PD13, PD14, PD15
 *					[DIO2]	PC6 , PC11, PC13, PC14, PC15, PD0 , PD1 , PD2
 *
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "digitalIO.h"

/* bit banding */
const u32 DIO_ODR_ADDR_BB[3][8] =
{
		{	0x424202A0, 0x424202A4, 0x424202A8, 0x424202AC, 0x424202B0, 0x424202B4, 0x424202B8, 0x424202BC	},
		{	0x4241828C, 0x4241829C, 0x424182A8, 0x424182AC, 0x424182B0, 0x424182B4, 0x424182B8, 0x424182BC	},
		{	0x42410298, 0x424102AC, 0x424102B4, 0x424102B8, 0x424102BC, 0x42418280, 0x42418284, 0x42418288	}
};

const u32 DIO_IDR_ADDR_BB[3][8] =
{
		{	0x42420220, 0x42420224, 0x42420228, 0x4242022c, 0x42420230, 0x42420234, 0x42420238, 0x4242023c	},
		{	0x4241820c, 0x4241821c, 0x42418228, 0x4241822c, 0x42418230, 0x42418234, 0x42418238, 0x4241823c	},
		{	0x42410218, 0x4241022c, 0x42410234, 0x42410238, 0x4241023c, 0x42418200, 0x42418204, 0x42418208	}
};

/* ------------------------------------------------------------
 * @関数名		:	DIO0_Init
 * @概要			:	Digital-IO0の初期化をします．
 * @引数-pin		:	設定するピンを8ビットで表し、1にしたビットの設定をします．
 * 	   　   -mode	:	1(DIO_MODE_IN )を設定すると入力として初期化
 * 	   				0(DIO_MODE_OUT)を設定すると出力として初期化
   --------------------------------------------------------- */
void DIO0_Init(u8 pin, int mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = (mode == 0  ? GPIO_Mode_OUT \
												: GPIO_Mode_IN);
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* PORTE */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = 0x0000;
	if(pin & 0x01)	GPIO_InitStructure.GPIO_Pin |= DIO0_0_PIN;	// PE8
	if(pin & 0x02)	GPIO_InitStructure.GPIO_Pin |= DIO0_1_PIN;	// PE9
	if(pin & 0x04)	GPIO_InitStructure.GPIO_Pin |= DIO0_2_PIN;	// PE10
	if(pin & 0x08)	GPIO_InitStructure.GPIO_Pin |= DIO0_3_PIN;	// PE11
	if(pin & 0x10)	GPIO_InitStructure.GPIO_Pin |= DIO0_4_PIN;	// PE12
	if(pin & 0x20)	GPIO_InitStructure.GPIO_Pin |= DIO0_5_PIN;	// PE13
	if(pin & 0x40)	GPIO_InitStructure.GPIO_Pin |= DIO0_6_PIN;	// PE14
	if(pin & 0x80)	GPIO_InitStructure.GPIO_Pin |= DIO0_7_PIN;	// PE15
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/* ------------------------------------------------------------
 * @関数名		:	DIO1_Init
 * @概要			:	Digital-IO1の初期化をします．
 * @引数-pin		:	設定するピンを8ビットで表し、1にしたビットの設定をします．
 * 	   　   -mode	:	1(DIO_MODE_IN )を設定すると入力として初期化
 * 	   				0(DIO_MODE_OUT)を設定すると出力として初期化
   --------------------------------------------------------- */
void DIO1_Init(u8 pin, int mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = (mode == 0  ? GPIO_Mode_OUT \
											    : GPIO_Mode_IN);
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* PORTD */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = 0x0000;
	if(pin & 0x01)	GPIO_InitStructure.GPIO_Pin |= DIO1_0_PIN;	// PD3
	if(pin & 0x02)	GPIO_InitStructure.GPIO_Pin |= DIO1_1_PIN;	// PD7
	if(pin & 0x04)	GPIO_InitStructure.GPIO_Pin |= DIO1_2_PIN;	// PD10
	if(pin & 0x08)	GPIO_InitStructure.GPIO_Pin |= DIO1_3_PIN;	// PD11
	if(pin & 0x10)	GPIO_InitStructure.GPIO_Pin |= DIO1_4_PIN;	// PD12
	if(pin & 0x20)	GPIO_InitStructure.GPIO_Pin |= DIO1_5_PIN;	// PD13
	if(pin & 0x40)	GPIO_InitStructure.GPIO_Pin |= DIO1_6_PIN;	// PD14
	if(pin & 0x80)	GPIO_InitStructure.GPIO_Pin |= DIO1_7_PIN;	// PD15
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/* ------------------------------------------------------------
 * @関数名		:	DIO2_Init
 * @概要			:	Digital-IO2の初期化をします．
 * @引数-pin		:	設定するピンを8ビットで表し、1にしたビットの設定をします．
 * 	   　   -mode	:	1(DIO_MODE_IN )を設定すると入力として初期化
 * 	   				0(DIO_MODE_OUT)を設定すると出力として初期化
   --------------------------------------------------------- */
void DIO2_Init(u8 pin, int mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = (mode == 0  ? GPIO_Mode_OUT \
											    : GPIO_Mode_IN);
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* PORTC */
	if(pin & 0x1F)
	{
		GPIO_InitStructure.GPIO_Pin = 0x0000;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		if(pin & 0x01)	GPIO_InitStructure.GPIO_Pin |= DIO2_0_PIN;	// PC6
		if(pin & 0x02)	GPIO_InitStructure.GPIO_Pin |= DIO2_1_PIN;	// PC11
		if(pin & 0x04)	GPIO_InitStructure.GPIO_Pin |= DIO2_2_PIN;	// PC13
		if(pin & 0x08)	GPIO_InitStructure.GPIO_Pin |= DIO2_3_PIN;	// PC14
		if(pin & 0x10)	GPIO_InitStructure.GPIO_Pin |= DIO2_4_PIN;	// PC15
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	}
	/* PORTD */
	if(pin & 0xE0)
	{
		GPIO_InitStructure.GPIO_Pin = 0x0000;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		if(pin & 0x20)	GPIO_InitStructure.GPIO_Pin |= DIO2_5_PIN;	// PD0
		if(pin & 0x40)	GPIO_InitStructure.GPIO_Pin |= DIO2_6_PIN;	// PD1
		if(pin & 0x80)	GPIO_InitStructure.GPIO_Pin |= DIO2_7_PIN;	// PD2
		GPIO_Init(GPIOD, &GPIO_InitStructure);
	}
}
