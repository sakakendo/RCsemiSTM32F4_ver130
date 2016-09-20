/***************************************************************************
 *	@�t�@�C����		:	motherboard.c
 *	@�T�v		:	MB���LED�C�v�b�V���X�C�b�`�C���[�^���[�X�C�b�`�̋@�\��񋟂��܂��D
 *					�ȉ��ɁC�e�v�f�̃s���z�u�������܂��D
 *					LED			0:PA8, 1:PB14
 *					PushSW		0:PE7
 *					RotarySW	0:PE2, 1:PE4, 2:PE5, 3:PE6
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "motherboard.h"

/* -------------------------------------------------
 * @�֐���	:	MB_LED_Init
 * @�T�v		:	MB��LED�ɐڑ�����Ă���GPIO(PA8, PB14)��
 * 				���������܂��D
 * @����		:	�Ȃ�
 * @�߂�l	:	�Ȃ�
 * ---------------------------------------------- */
void MB_LED_Init(void)
{
	/* �N���b�N���� */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* GPIO�ݒ� */
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
 * @�֐���	:	MB_LED_TurnOff
 * @�T�v		:	�w���LED���������܂��D
 * @����-num	:	LED�̔ԍ��A0, 1
 * @�߂�l	:	�Ȃ�
 * ---------------------------------------------- */
void MB_LED_TurnOff(int num)
{
	if     (num == 0) GPIOA->BSRRH = GPIO_Pin_8;
	else if(num == 1) GPIOB->BSRRH = GPIO_Pin_14;
}

/* -------------------------------------------------
 * @�֐���	:	MB_LED_TurnOn
 * @�T�v		:	�w���LED��_�����܂��D
 * @����-num	:	LED�̔ԍ��A0, 1
 * @�߂�l	:	�Ȃ�
 * ---------------------------------------------- */
void MB_LED_TurnOn(int num)
{
	if     (num == 0) GPIOA->BSRRL = GPIO_Pin_8;
	else if(num == 1) GPIOB->BSRRL = GPIO_Pin_14;
}

/* -------------------------------------------------
 * @�֐���	:	MB_LED_Toggle
 * @�T�v		:	�w���LED��O��ƈႤ��Ԃɂ��܂��D
 * @����-num	:	LED�̔ԍ��A0, 1
 * @�߂�l	:	�Ȃ�
 * ---------------------------------------------- */
void MB_LED_Toggle(int num)
{
	if     (num == 0) GPIOA->ODR ^= GPIO_Pin_8;
	else if(num == 1) GPIOB->ODR ^= GPIO_Pin_14;
}

/* -------------------------------------------------
 * @�֐���	:	MB_PushSW_Init
 * @�T�v		:	�v�b�V���X�C�b�`�ɐڑ�����Ă���GPIO(PE7)��
 * 				�����������܂��D
 * @����		:	�Ȃ�
 * @�߂�l	:	�Ȃ�
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
 * @�֐���	:	MB_PushSW_IsPushed
 * @�T�v		:	�v�b�V���X�C�b�`�������ꂽ���ǂ������肵�܂��D
 * @����		:	�Ȃ�
 * @�߂�l	:	�����ꂽ��1, �����łȂ����0
 * ---------------------------------------------- */
int MB_PushSW_IsPushed(void)
{
	if(GPIOE->IDR & GPIO_Pin_7)	return 1;
	else						return 0;
}

/* -------------------------------------------------
 * @�֐���	:	MB_RotarySW_Init
 * @�T�v		:	���[�^���[�X�C�b�`�ɐڑ�����Ă���
 * 				GPIO(PE2, PE4, PE5, PE6)�̏����������܂��D
 * @����		:	�Ȃ�
 * @�߂�l	:	�Ȃ�
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
 * @�֐���	:	MB_RotarySW_Check
 * @�T�v		:	���[�^���[�X�C�b�`�������l(0-15)�𔻕ʂ��܂��D
 * @����		:	�Ȃ�
 * @�߂�l	:	���[�^���[�X�C�b�`�̒l(0-15)
 * ---------------------------------------------- */
u8 MB_RotarySW_Check(void)
{
	return (((GPIOE->IDR & GPIO_Pin_2) >> 2) | ((GPIOE->IDR & GPIO_Pin_4) >> 3) |
			((GPIOE->IDR & GPIO_Pin_5) >> 3) | ((GPIOE->IDR & GPIO_Pin_6) >> 3));

}
