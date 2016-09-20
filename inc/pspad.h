/***************************************************************************
 *	@�t�@�C����		:	pspad.h
 *	@�T�v		:	USART3(�d�b��),USART2(Bluetooth)�ɂ�����PS�R���g���[���Ƃ̒ʐM��
 *					�񋟂���D
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#ifndef __PSPAD_H__
#define __PSPAD_H__

/* �^��`	============================================================= */
typedef union
{
    struct
    {
        u8 d1			: 1; /*�����܂ő�0�o�C�g*/
        u8 LStick		: 1; /*���X�e�B�b�N��������*/
        u8 L2			: 1;
        u8 L1			: 1;
        u8 UpArrow		: 1; /*�����̏���*/
        u8 RightArrow	: 1; /*�����̉E���*/
        u8 DownArrow	: 1; /*�����̉����*/
        u8 LeftArrow	: 1; /*�����̍����*/
        u8 d2			: 1; /*�����܂ő�1�o�C�g*/
        u8 RStick		: 1; /*�E�X�e�B�b�N��������*/
        u8 R2			: 1;
        u8 R1			: 1;
        u8 Triangle		: 1; /*�E���́��{�^��*/
        u8 Circle		: 1; /*�E���́��{�^��*/
        u8 Cross		: 1; /*�E���́~�{�^��*/
        u8 Square		: 1; /*�E���́��{�^��*/
        u8 d3			: 1; /*�����܂ő�2�o�C�g*/
        u8 Start		: 1; /*Start�{�^��*/
        u8 dd3			: 2;
        u8 RStick_X		: 4;
        u8 d4			: 1; /*�����܂ő�3�o�C�g*/
        u8 Select		: 1; /*Select�{�^��*/
        u8 dd4			: 2;
        u8 RStick_Y		: 4;
        u8 d5			: 1; /*�����܂ő�4�o�C�g*/
        u8 Mode			: 1; /*���[�h�@�A�i���O�F0�@�f�B�W�^���F1*/
        u8 dd5			: 2;
        u8 LStick_X		: 4;
        u8 d6			: 1; /*�����܂ő�5�o�C�g*/
        u8 Error		: 1; /*��M���̃G���[�@�G���[�F1�@����F0*/
        u8 dd6			: 2;
        u8 LStick_Y		: 4;
        u8 CheckSum;    	 /*�`�F�b�N�T���{�P�����*/
    } name;
    u8 bytes[7];
} psdata_format_t;

/* �萔��`	============================================================= */
#define PS_RECV_TIMEOUT_MS	100

/* �L�[�R���t�B�O */
#define PS_B_R1(ps)			ps.name.R1
#define PS_B_R2(ps)			ps.name.R2
#define PS_B_L1(ps)			ps.name.L1
#define PS_B_L2(ps)			ps.name.L2
#define PS_B_TRIANGLE(ps)	ps.name.Triangle
#define PS_B_CIRCLE(ps)		ps.name.Circle
#define PS_B_CROSS(ps)		ps.name.Cross
#define PS_B_SQUARE(ps)		ps.name.Square
#define PS_B_START(ps)		ps.name.Start
#define PS_B_SELECT(ps)		ps.name.Select
#define PS_B_ARROW_U(ps)	ps.name.UpArrow
#define PS_B_ARROW_R(ps)	ps.name.RightArrow
#define PS_B_ARROW_D(ps)	ps.name.DownArrow
#define PS_B_ARROW_L(ps)	ps.name.LeftArrow
#define PS_B_STICK_R(ps)		ps.name.RStick
#define PS_B_STICK_L(ps)		ps.name.LStick
#define PS_STICK_RX(ps)		ps.name.RStick_X
#define PS_STICK_RY(ps)		ps.name.RStick_Y
#define PS_STICK_LX(ps)		ps.name.LStick_X
#define PS_STICK_LY(ps)		ps.name.LStick_Y

/* �ϐ��v���g�^�C�v�錾	===================================================== */
extern const int psdata_convertTable[16];

/* �֐��v���g�^�C�v�錾	===================================================== */
/* -------------------------------------------------
 * @�֐���		:	USART2_BDMaster_Init
 * @�T�v			:	USART2(Bluetooth)�Ƃ̒ʐM��
 * 					�������}�X�^�[�Ƃ��ď�����
 * @����-command	:	���������Ɏ����ԐM���镶����
 * @�߂�l		:	�Ȃ�
 * ---------------------------------------------- */
void USART2_BDMaster_Init(char *command);

/* -------------------------------------------------
 * @�֐���		:	USART3_BDMaster_Init
 * @�T�v			:	USART3(�d�b��)�Ƃ̒ʐM��
 * 					�������}�X�^�[�Ƃ��ď�����
 * @����-command	:	���������Ɏ����ԐM���镶����
 * @�߂�l		:	�Ȃ�
   ---------------------------------------------- */
void USART3_BDMaster_Init(char *command);

/* -------------------------------------------------
 * @�֐���		:	USART2_BDSlave_Init
 * @�T�v			:	USART2(Bluetooth)�Ƃ̒ʐM��
 * 					�������X���[�u�Ƃ��ď�����
 * @����-command	:	���������Ɏ����ԐM���镶����
 * @�߂�l		:	�Ȃ�
 * ---------------------------------------------- */
void USART2_BDSlave_Init(char *command);

/* -------------------------------------------------
 * @�֐���		:	USART3_BDSlave_Init
 * @�T�v			:	USART3(�d�b��)�Ƃ̒ʐM��
 * 					�������X���[�u�Ƃ��ď�����
 * @����-command	:	���������Ɏ����ԐM���镶����
 * @�߂�l		:	�Ȃ�
   ---------------------------------------------- */
void USART3_BDSlave_Init(char *command);

/* -------------------------------------------------
 * @�֐���		:	USART2_PSdata_Recv
 * @�T�v			:	USART2(�d�b��)����
 * 					PS�R���g���[���̃f�[�^����M����D
 * @����-psdata	:	�R���g���[���f�[�^�i�[��̕ϐ�
 * @�߂�l		:	�Ȃ�
 * ---------------------------------------------- */
void USART2_PSdata_Recv(psdata_format_t *psdata);

/* -------------------------------------------------
 * @�֐���		:	USART3_PSdata_Recv
 * @�T�v			:	USART3(�d�b��)����
 * 					PS�R���g���[���̃f�[�^����M����D
 * @����-psdata	:	�R���g���[���f�[�^�i�[��̕ϐ�
 * @�߂�l		:	�Ȃ�
 * ---------------------------------------------- */
void USART3_PSdata_Recv(psdata_format_t *psdata);

#endif /* __PSPAD_H__ */
