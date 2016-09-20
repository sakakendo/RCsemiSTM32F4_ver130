/***************************************************************************
 *	@�t�@�C����		:	rotary_encoder.h
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

#ifndef __ROTARY_ENCODER_H__
#define __ROTARY_ENCODER_H__

/* �C���N���[�h	============================================================= */
#include <stm32f4xx.h>

/* �萔��`	============================================================= */
/* ���[�^���[�G���R�[�_���g�p����^�C�} */
#define ENC0_TIM	TIM2
#define ENC1_TIM	TIM3

/* ���[�^���[�G���R�[�_���g�p����|�[�g�Ȃ� */
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

/* �}�N����`	============================================================= */
/* -------------------------------------------------
 * @�}�N����	:	ENCm_CheckCNT
 * @�T�v		:	���[�^���[�G���R�[�_�̒l��ǂݎ��
 * @����		:	�Ȃ�
 * @�߂�l	:	-2^16 ~ 2^16-1�͈̔͂ł̃J�E���^�̒l
 * @���ӓ_	:	�G���R�[�_�̒l��16bit�𒴂���ƃI�[�o�[�t���[����
 * 				�ݐς��v�Z���l���N���A����ȂǑ΍􂷂邱��
 *				<��>enc += ENC_ReadCNT();
 * 				    ENC_ClearCNT(ENC0_CH);
 * ---------------------------------------------- */
#define ENC0_CheckCNT()	((signed short)ENC0_TIM->CNT)
#define ENC1_CheckCNT()	((signed short)ENC1_TIM->CNT)
#define ENC2_CheckCNT()	((signed short)gENC2_CNT)
#define ENC3_CheckCNT()	((signed short)gENC3_CNT)

/* -------------------------------------------------
 * @�}�N����	:	ENC_CheckCNT
 * @�T�v		:	���[�^���[�G���R�[�_�̒l��ǂݎ��
 * @����-ch	:	�ǂݎ�郍�[�^���[�G���R�[�_
 * @�߂�l	:	-2^16 ~ 2^16-1�͈̔͂ł̃J�E���^�̒l
 * @���ӓ_	:	ENCn_ReadCNT�Ɠ��l�D
 * 				���݂��Ȃ��`�����l����I�������ꍇ0��Ԃ�
 * ---------------------------------------------- */
#define ENC_CheckCNT(ch)	((ch) == 0 ? ENC0_CheckCNT() : \
						 	 (ch) == 1 ? ENC1_CheckCNT() : \
						 	 (ch) == 2 ? ENC2_CheckCNT() : \
						 	 (ch) == 3 ? ENC3_CheckCNT() : 0)

/* -------------------------------------------------
 * @�}�N����	:	ENCn_ClearCNT
 * @�T�v		:	���[�^���[�G���R�[�_�̃J�E���g�̒l�����Z�b�g����
 * @����		:	�Ȃ�
 * @�߂�l	:	�Ȃ�
 * @���ӓ_	:	ENC_ReadCNT�֐��Ɠ��l
 * ---------------------------------------------- */
#define ENC0_ClearCNT()	(ENC0_TIM->CNT = 0)
#define ENC1_ClearCNT()	(ENC1_TIM->CNT = 0)
#define ENC2_ClearCNT()	(gENC2_CNT = 0)
#define ENC3_ClearCNT()	(gENC3_CNT = 0)

/* -------------------------------------------------
 * @�}�N����	:	ENC_ClearCNT
 * @�T�v		:	���[�^���[�G���R�[�_�̃J�E���g�̒l�����Z�b�g����
 * @����-ch	:	�N���A���郍�[�^���[�G���R�[�_
 * @�߂�l	:	�Ȃ�
 * @���ӓ_	:	ENCn_ClearCNT�֐��Ɠ��l�D
 * 				���݂��Ȃ��`�����l����I�񂾏ꍇ�������Ȃ�
 * ---------------------------------------------- */
#define ENC_ClearCNT(ch)	((ch) == 0 ? ENC0_ClearCNT() : \
					  	 	 (ch) == 1 ? ENC1_ClearCNT() : \
					  	 	 (ch) == 2 ? ENC2_ClearCNT() : \
					  	 	 (ch) == 3 ? ENC3_ClearCNT() : 0)

/* �ϐ��v���g�^�C�v�錾	===================================================== */
extern signed short gENC2_CNT, gENC3_CNT;

/* �֐��v���g�^�C�v�錾	===================================================== */
/* -------------------------------------------------
 * @�֐���	:	ENCn_Init
 * @�T�v		:	���[�^���[�G���R�[�_�̏�����������
 * @����		:	�Ȃ�
 * @�߂�l	:	�Ȃ�
 * ---------------------------------------------- */
void ENC0_Init(void);
void ENC1_Init(void);
void ENC2_Init(void);
void ENC3_Init(void);

#endif /* __ROTARY_ENCODER_H__ */
