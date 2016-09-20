/***************************************************************************
 *	@�t�@�C����		:	rotary_encoder.c
 *	@�T�v		:	���[�^���[�G���R�[�_�|�[�g�̏������ƁC�ǂݎ���񋟂���D
 *					�|�[�g��ENC0-3������C�g�p����^�C�}�CGPIO�͈ȉ��̂Ƃ���C
 *					ENC0	:TIM2	A:PA15 / B:PB3
 *					ENC1	:TIM3	A:PB4  / B:PB5
 *					ENC2	:TIM4	A:PB7  / B:PB8
 *					ENC3	:TIM8	A:PC8  / B:PC9
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "rotary_encoder.h"

signed short gENC2_CNT = 0, gENC3_CNT = 0;

/* -------------------------------------------------
 * @�֐���	:	ENCn_Init
 * @�T�v		:	���[�^���[�G���R�[�_�̏�����������
 * @����		:	�Ȃ�
 * @�߂�l	:	�Ȃ�
 * ---------------------------------------------- */
void ENC0_Init(void)
{
	/* �N���b�N������ */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* GPIO�̏����� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// �v���A�b�v��R�͊O���Őڑ��ς�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* GPIO�s�����^�C�}�Ƃ��ė��p����ݒ� */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3 , GPIO_AF_TIM2);

	/* �^�C�}�̐ݒ� */
	TIM_DeInit(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period 		= 0xffff;	// �ő�l
	TIM_TimeBaseStructure.TIM_Prescaler 	= 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* ���[�^���[�G���R�[�_�ݒ� */
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,
							   TIM_ICPolarity_Rising,
							   TIM_ICPolarity_Rising);
	// �^�C�}��L����
	TIM_Cmd(TIM2, ENABLE);
}

void ENC1_Init(void)
{
	/* �N���b�N������ */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* GPIO�̏����� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// �v���A�b�v��R�͊O���Őڑ��ς�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* GPIO�s�����^�C�}�Ƃ��ė��p����ݒ� */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);

	/* �^�C�}�̐ݒ� */
	TIM_DeInit(TIM3);	// �K�v�Ȃ���������Ȃ�
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period 		= 0xffff;	// �ő�l
	TIM_TimeBaseStructure.TIM_Prescaler 	= 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* ���[�^���[�G���R�[�_�ݒ� */
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,
							   TIM_ICPolarity_Rising,
							   TIM_ICPolarity_Rising);
	// �^�C�}��L����
	TIM_Cmd(TIM3, ENABLE);
}

void ENC2_Init(void)
{
	/* �N���b�N������ */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* GPIO�̏����� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// �v���A�b�v��R�͊O���Őڑ��ς�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	gENC2_CNT = 0;
}

void ENC3_Init(void)
{
	/* �N���b�N������ */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* GPIO�̏����� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;	// �v���A�b�v��R�͊O���Őڑ��ς�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	gENC3_CNT = 0;
}
