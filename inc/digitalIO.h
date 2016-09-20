/***************************************************************************
 *	@�t�@�C����		:	digitalIO.h
 *	@�T�v		:	DIGITAL-IOx�|�[�g��p���āC�f�W�^���I�ȓ��o�͂��s���܂��D
 *					�ȉ��Ƀ}�U�[�{�[�h��ɐ݂����Ă���DIGITAL-IOx�̃s���z�u�������܂��D
 *
 *					[DIO0]	PE8 , PE9 , PE10, PE11, PE12, PE13, PE14, PE15
 *					[DIO1]	PD3 , PD7 , PD10, PD11, PD12, PD13, PD14, PD15
 *					[DIO2]	PC6 , PC11, PC13, PC14, PC15, PD0 , PD1 , PD2
 *
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#ifndef __DIGITALIO_H__
#define __DIGITALIO_H__

/* �C���N���[�h	============================================================= */
#include <stm32f4xx.h>

/* �萔��`	============================================================= */
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

/* ���o�͐ݒ� */
#define DIO_MODE_OUT	0
#define DIO_MODE_IN		1

/* �}�N����`	============================================================= */
/* ------------------------------------------------------------
 * @�}�N����		:	DIO_OutputPin
 * @�T�v			:	Digital-IOx���� "0"(0V) or "1"(3V) ���o�͂��܂��D
 * @����	-port	:	�o�̓|�[�g��I�����܂�(0-2)�D
 * 		-pin	:	�o�̓s����I�����܂�(0-7)�D
 * 		-status	:	�o�͂̐M��(0, 1)
 * @���ӓ_		:	�K��O�̒�����������I������ƁC�������̂ǂ����̒l��
 * 					��������邱�ƂɂȂ�܂��D
 * --------------------------------------------------------- */
#define DIO_OutputPin(port, pin, status)	(*((u32*)DIO_ODR_ADDR_BB[port][pin]) = (status))

/* ------------------------------------------------------------
 * @�}�N����		:	DIO_TogglePin
 * @�T�v			:	���O��Digital-IOx�̏o�͏�Ԃ𔽓]�����܂��D
 * @����-port	:	�o�̓|�[�g��I�����܂�(0-2)�D
 * 	   �@   -pin		:	�o�̓s����I�����܂�(0-7)�D
 * @���ӓ_		:	�K��O�̒�����������I������ƁC�������̂ǂ����̒l��
 * 					��������邱�ƂɂȂ�܂��D
   --------------------------------------------------------- */
#define DIO_TogglePin(port, pin)	(*((u32*)DIO_ODR_ADDR_BB[port][pin]) ^= 1)

/* ------------------------------------------------------------
 * @�}�N����		:	DIO_CheckPin
 * @�T�v			:	DigitalIOx�����͂����M����ǂݎ��܂��D
 * @����-port	:	���̓|�[�g��I�����܂�(0-2)�D
 * 	   �@   -pin		:	���̓s����I�����܂�(0-7)�D
 * @���ӓ_		:	�K��O�̈�����I������ƁC�������̂ǂ����̒l��
 * 					��������邱�ƂɂȂ�܂��D
   --------------------------------------------------------- */
#define DIO_CheckPin(port, pin)	(*((u32*)DIO_IDR_ADDR_BB[port][pin]))

/* �ϐ��v���g�^�C�v�錾	===================================================== */
/* GPIOx��ODR�̃r�b�g�o���h */
extern const u32 DIO_ODR_ADDR_BB[3][8];

/* GPIOx��IDR�̃r�b�g�o���h */
extern const u32 DIO_IDR_ADDR_BB[3][8];

/* �֐��v���g�^�C�v�錾	===================================================== */
/* ------------------------------------------------------------
 * @�֐���		:	DIO0_Init
 * @�T�v			:	Digital-IO0�̏����������܂��D
 * @����-pin		:	�ݒ肷��s����8�r�b�g�ŕ\���A1�ɂ����r�b�g�̐ݒ�����܂��D
 * 	   �@   -mode	:	1(DIO_MODE_IN )��ݒ肷��Ɠ��͂Ƃ��ď�����
 * 	   				0(DIO_MODE_OUT)��ݒ肷��Əo�͂Ƃ��ď�����
   --------------------------------------------------------- */
void DIO0_Init(u8 pin, int mode);

/* ------------------------------------------------------------
 * @�֐���		:	DIO1_Init
 * @�T�v			:	Digital-IO1�̏����������܂��D
 * @����-pin		:	�ݒ肷��s����8�r�b�g�ŕ\���A1�ɂ����r�b�g�̐ݒ�����܂��D
 * 	   �@   -mode	:	1(DIO_MODE_IN )��ݒ肷��Ɠ��͂Ƃ��ď�����
 * 	   				0(DIO_MODE_OUT)��ݒ肷��Əo�͂Ƃ��ď�����
   --------------------------------------------------------- */
void DIO1_Init(u8 pin, int mode);

/* ------------------------------------------------------------
 * @�֐���		:	DIO2_Init
 * @�T�v			:	Digital-IO2�̏����������܂��D
 * @����-pin		:	�ݒ肷��s����8�r�b�g�ŕ\���A1�ɂ����r�b�g�̐ݒ�����܂��D
 * 	   �@   -mode	:	1(DIO_MODE_IN )��ݒ肷��Ɠ��͂Ƃ��ď�����
 * 	   				0(DIO_MODE_OUT)��ݒ肷��Əo�͂Ƃ��ď�����
   --------------------------------------------------------- */
void DIO2_Init(u8 pin, int mode);

#endif /* __DIGITALIO_H__ */
