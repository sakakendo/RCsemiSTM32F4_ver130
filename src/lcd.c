/***************************************************************************
 *	@ファイル名		:	lcd.c
 *	@概要		:	SPI通信にて，グラフィックディスプレイ(DOGS102-6)を制御します．
 *					~RESET	:	PB11
 *					RS		:	PB12
 *					SCK		:	PB13
 *					MOSI	:	PB15
 *	@バージョン		:	1.2.0
 *	@開発者		:	キネクト
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "timer.h"
#include "lcd.h"
#include "tri_S_Font6x8_90.h"

static u16 charpos_x, charpos_y;

/* 初期化コマンド */
static const unsigned char init_seq[] =
{
    0x40,    // Display start line 0
    0xa0,    // ADC reverse
    0xc8,    // Normal COM0...COM63
    0xa6,    // Display normal
    0xa2,    // Set Bias 1/9 (Duty 1/65)
    0x2f,    // Booster, Regulator and Follower On
    0xf8,    // Set internal Booster to 4x
    0x00,
    0x27,    // Contrast set
    0x81,
    0x09,
    0xac,    // No indicator
    0x00,
    0xaf,    // Display on
};

/***************************************************
 * @関数名		:	LCD_Send_Command
 * @概要			:	LCDに制御コマンドを送信します．
 * @引数	-buf	:	コマンド(1[Byte])
 * @戻り値		:	なし
 ************************************************ */
void LCD_Send_Command(u8 cmd)
{
	GPIOB->BSRRH = GPIO_Pin_12;
	SPI2->DR = cmd;
	while(!SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE));
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY));
}

/***************************************************
 * @関数名		:	LCD_Send_Data
 * @概要			:	LCDにデータを送信します．
 * @引数	-data	:	データ(1[Byte])
 * @戻り値		:	なし
 ************************************************ */
void LCD_Send_Data(u8 data)
{
	GPIOB->BSRRL = GPIO_Pin_12;
	SPI2->DR = data;
	while(!SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE));
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY));
}

/***************************************************
 * @関数名	:	LCD_Init
 * @概要		:	MB上のLCD(DOGS102N-6)を初期化します．
 * @引数		:	なし
 * @戻り値	:	なし
 ************************************************ */
void LCD_Init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	SPI_InitTypeDef		SPI_InitStructure;
	int i;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 , ENABLE);

	/* CS, RESET, CD */
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIOB->BSRRH = GPIO_Pin_11 | GPIO_Pin_12;

	/* SCK, MOSI */
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);

	SPI_StructInit(&SPI_InitStructure);
	SPI_InitStructure.SPI_Direction			= SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode				= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize			= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL				= SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA				= SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS				= SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit			= SPI_FirstBit_MSB;

	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);

	/* DOGS Reset */
	GPIOB->BSRRL = GPIO_Pin_11;
	delay_ms(50);
	GPIOB->BSRRH = GPIO_Pin_11;
	delay_ms(50);
	GPIOB->BSRRL = GPIO_Pin_11;
	delay_ms(50);

	for(i = 0; i < sizeof(init_seq); i++)
	{
		LCD_Send_Command(init_seq[i]);
	}
}

/***************************************************
 * @関数名	:	LCD_LocatePixel
 * @概要		:	LCDの指定座標を変更します．
 * @引数	-x	:	指定X座標
 * 		-y	:	指定Y座標
 * @戻り値	:	なし
 ************************************************ */
static void LCD_LocatePixel(int x, int y)
{
	u8 page, column_h, column_l;
	page = y/8;
	x += 30;
	column_h = ((x&0xF0)>>4);
	column_l =  (x&0x0F);
	LCD_Send_Command(0xB0+page);
	LCD_Send_Command(0x10+column_h);
	LCD_Send_Command(0x00+column_l);
}

/***************************************************
 * @関数名	:	LCD_Clear
 * @概要		:	LCDの表示領域をクリアします．
 * @引数		:	なし
 * @戻り値	:	なし
 ************************************************ */
void LCD_Clear(void)
{
	u8 i, j;
	for(i = 0; i < 8; i++)
	{
		LCD_LocatePixel(0, i*8);
		for(j = 0; j < LCD_WIDTH; j++)
		{
			LCD_Send_Data(0x00);	// Clear
		}
	}
}

/***************************************************
 * @関数名	:	LCD_DrawDot
 * @概要		:	LCDに1ピクセルの点を描画します．
 * @引数	-x	:	指定X座標
 * 		-y	:	指定Y座標
 * @戻り値	:	なし
 ************************************************ */
void LCD_DrawDot(int x, int y)
{
	LCD_LocatePixel(x, y);
	LCD_Send_Data(0x01<<(y&0x07));
}

/***************************************************
 * @関数名		:	LCD_LocateChar
 * @概要			:	LCDの文字指定座標を変更します．
 * @引数	-column	:	指定行座標
 * 		-row	:	指定列座標
 * @戻り値		:	なし
 ************************************************ */
void LCD_LocateChar(int column, int row)
{
	charpos_x = column;
	charpos_y = row;
}

/***************************************************
 * @関数名			:	LCD_DrawChar
 * @概要				:	LCDに1バイト文字を表示します．
 * @引数	-AsciiCode	:	ASCIIコードでの文字を指定．
 * @戻り値			:	なし
 ************************************************ */
void LCD_DrawChar(char AsciiCode)
{
	int data, i;

	if(AsciiCode == '\n')
	{
		if(++charpos_y == 65535U)	charpos_y = 0;
		return;
	}
	if(AsciiCode == '\r')
	{
		charpos_x = 0;
		return;
	}

	data = AsciiCode*6;

	LCD_LocatePixel(charpos_x*6, charpos_y*8);
	for(i = 0; i < 6; i++)
	{
		LCD_Send_Data(tri_S_uchrFont6x8_90[data+i]);
	}

	if(++charpos_x == 65535U)	charpos_x = 0;
}

/***************************************************
 * @関数名		:	LCD_ScrollPixel
 * @概要			:	LCDを指定ピクセルだけ縦にスクロールします．
 * @引数	-num	:	スクロールするピクセル数
 * @戻り値		:	なし
 ************************************************ */
void LCD_ScrollPixel(u8 num)
{
	LCD_Send_Command(0x40|num);
}
