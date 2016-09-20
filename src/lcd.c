/***************************************************************************
 *	@�t�@�C����		:	lcd.c
 *	@�T�v		:	SPI�ʐM�ɂāC�O���t�B�b�N�f�B�X�v���C(DOGS102-6)�𐧌䂵�܂��D
 *					~RESET	:	PB11
 *					RS		:	PB12
 *					SCK		:	PB13
 *					MOSI	:	PB15
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "timer.h"
#include "lcd.h"
#include "tri_S_Font6x8_90.h"

static u16 charpos_x, charpos_y;

/* �������R�}���h */
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
 * @�֐���		:	LCD_Send_Command
 * @�T�v			:	LCD�ɐ���R�}���h�𑗐M���܂��D
 * @����	-buf	:	�R�}���h(1[Byte])
 * @�߂�l		:	�Ȃ�
 ************************************************ */
void LCD_Send_Command(u8 cmd)
{
	GPIOB->BSRRH = GPIO_Pin_12;
	SPI2->DR = cmd;
	while(!SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE));
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY));
}

/***************************************************
 * @�֐���		:	LCD_Send_Data
 * @�T�v			:	LCD�Ƀf�[�^�𑗐M���܂��D
 * @����	-data	:	�f�[�^(1[Byte])
 * @�߂�l		:	�Ȃ�
 ************************************************ */
void LCD_Send_Data(u8 data)
{
	GPIOB->BSRRL = GPIO_Pin_12;
	SPI2->DR = data;
	while(!SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE));
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY));
}

/***************************************************
 * @�֐���	:	LCD_Init
 * @�T�v		:	MB���LCD(DOGS102N-6)�����������܂��D
 * @����		:	�Ȃ�
 * @�߂�l	:	�Ȃ�
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
 * @�֐���	:	LCD_LocatePixel
 * @�T�v		:	LCD�̎w����W��ύX���܂��D
 * @����	-x	:	�w��X���W
 * 		-y	:	�w��Y���W
 * @�߂�l	:	�Ȃ�
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
 * @�֐���	:	LCD_Clear
 * @�T�v		:	LCD�̕\���̈���N���A���܂��D
 * @����		:	�Ȃ�
 * @�߂�l	:	�Ȃ�
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
 * @�֐���	:	LCD_DrawDot
 * @�T�v		:	LCD��1�s�N�Z���̓_��`�悵�܂��D
 * @����	-x	:	�w��X���W
 * 		-y	:	�w��Y���W
 * @�߂�l	:	�Ȃ�
 ************************************************ */
void LCD_DrawDot(int x, int y)
{
	LCD_LocatePixel(x, y);
	LCD_Send_Data(0x01<<(y&0x07));
}

/***************************************************
 * @�֐���		:	LCD_LocateChar
 * @�T�v			:	LCD�̕����w����W��ύX���܂��D
 * @����	-column	:	�w��s���W
 * 		-row	:	�w�����W
 * @�߂�l		:	�Ȃ�
 ************************************************ */
void LCD_LocateChar(int column, int row)
{
	charpos_x = column;
	charpos_y = row;
}

/***************************************************
 * @�֐���			:	LCD_DrawChar
 * @�T�v				:	LCD��1�o�C�g������\�����܂��D
 * @����	-AsciiCode	:	ASCII�R�[�h�ł̕������w��D
 * @�߂�l			:	�Ȃ�
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
 * @�֐���		:	LCD_ScrollPixel
 * @�T�v			:	LCD���w��s�N�Z�������c�ɃX�N���[�����܂��D
 * @����	-num	:	�X�N���[������s�N�Z����
 * @�߂�l		:	�Ȃ�
 ************************************************ */
void LCD_ScrollPixel(u8 num)
{
	LCD_Send_Command(0x40|num);
}
