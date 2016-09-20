/***************************************************************************
 *	@�t�@�C����		:	pspad.c
 *	@�T�v		:	USART3(�d�b��),USART2(Bluetooth)�ɂ�����PS�R���g���[���Ƃ̒ʐM��
 *					�񋟂���D
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "usart.h"
#include "pspad.h"
#include "timer.h"

/* -------------------------------------------------
 * @�֐���		:	Coincidence_Check
 * @�T�v			:	str1�̐擪����num������str2�Ɣ�r����
 * @����	-str1	:	���r�Ώە�����
 * 		-str2	:	��r������
 * 		-num	:	str1�̐擪�����r���镶����
 * @�߂�l		:	��v����1������ȊO��0��Ԃ�
   ---------------------------------------------- */
static int Coincidence_Check(const char *str1, const char *str2, int num)
{
	int i;
	for(i = 0; i < num; i++)
		if (*str1++ != *str2++)	return 0;
	return 1;
}

/* -------------------------------------------------
 * @�֐���		:	PS_CheckSum
 * @�T�v			:	PS�R���g���[������̎�M�`�F�b�N�T���𒲍�����
 * @����-psdata	:	PS�R���g���[������󂯎�����f�[�^
 * @�߂�l		:	�`�F�b�N�T�����^�Ȃ�1�A�U�Ȃ��0��Ԃ�
   ---------------------------------------------- */
static int PSdata_CheckSum(psdata_format_t *psdata)
{
	u8 sum = 0;
	int i;
	for(i = 0; i < 6; i++)	sum += psdata->bytes[i];
	if(psdata->bytes[6]-1 == sum)	return 1;
	else							return 0;
}

/* -------------------------------------------------
 * @�֐���		:	USART2_BDMaster_Init
 * @�T�v			:	USART2(Bluetooth)�Ƃ̒ʐM��
 * 					�������}�X�^�[�Ƃ��ď�����
 * @����-command	:	���������Ɏ����ԐM���镶����
 * @�߂�l		:	�Ȃ�
 * ---------------------------------------------- */
void USART2_BDMaster_Init(char *command)
{
	char buff[128];
	USART2_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "OK", 2))
	{
		USART2_RecvString(buff, 128);
	}
	if(command)
	{
		USART2_SendString(command);
		USART2_SendString("\r\n");
	}
	USART2_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "CONNECT", 7))
	{//Slave�Ƃ̐ڑ�����������܂őҋ@�B
		USART2_RecvString(buff, 128);
	}
}

/* -------------------------------------------------
 * @�֐���		:	USART3_BDMaster_Init
 * @�T�v			:	USART3(�d�b��)�Ƃ̒ʐM��
 * 					�������}�X�^�[�Ƃ��ď�����
 * @����-command	:	���������Ɏ����ԐM���镶����
 * @�߂�l		:	�Ȃ�
   ---------------------------------------------- */
void USART3_BDMaster_Init(char *command)
{
	char buff[128];
	USART3_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "OK", 2))
	{
		USART3_RecvString(buff, 128);
	}
	if(command)
	{
		USART3_SendString(command);
		USART3_SendString("\r\n");
	}
	USART3_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "CONNECT", 7))
	{//Slave�Ƃ̐ڑ�����������܂őҋ@�B
		USART3_RecvString(buff,128);
	}
}

/* -------------------------------------------------
 * @�֐���		:	USART2_BDSlave_Init
 * @�T�v			:	USART2(Bluetooth)�Ƃ̒ʐM��
 * 					�������X���[�u�Ƃ��ď�����
 * @����-command	:	���������Ɏ����ԐM���镶����
 * @�߂�l		:	�Ȃ�
 * ---------------------------------------------- */
void USART2_BDSlave_Init(char *command)
{
	char buff[128];
	USART2_RecvString(buff, 128); //"OK"���󂯂��͂�
	while(!Coincidence_Check(buff, "OK", 2))
	{
		USART2_RecvString(buff, 128);
	}
	if(command)
	{
		USART2_SendString(command);
		USART2_SendString("\r\n");
	}
	USART2_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "CONNECT", 7))
	{//Master�Ƃ̐ڑ�����������܂őҋ@�B
		USART2_RecvString(buff, 128);
	}
}

/* -------------------------------------------------
 * @�֐���		:	USART3_BDSlave_Init
 * @�T�v			:	USART3(�d�b��)�Ƃ̒ʐM��
 * 					�������X���[�u�Ƃ��ď�����
 * @����-command	:	���������Ɏ����ԐM���镶����
 * @�߂�l		:	�Ȃ�
   ---------------------------------------------- */
void USART3_BDSlave_Init(char *command)
{
	char buff[128];
	USART3_RecvString(buff, 128); //"OK"���󂯂��͂�
	while(!Coincidence_Check(buff, "OK", 2))
	{
		USART3_RecvString(buff, 128);
	}
	if(command)
	{
		USART3_SendString(command);
		USART3_SendString("\r\n");
	}
	USART3_RecvString(buff, 128);
	while(!Coincidence_Check(buff, "CONNECT", 7))
	{//Master�Ƃ̐ڑ�����������܂őҋ@�B
		USART3_RecvString(buff, 128);
	}
}

/* -------------------------------------------------
 * @�֐���	:	USART2_PSpacket_Recv
 * @�T�v		:	USART2(Bluetooth)����
 * 				PS�R���g���[���̃p�P�b�g(7Byte)���󂯎��
 * @����-buf	:	�󂯎���������i�[����ϐ�
 * @�߂�l	:	��񂪎�����7���A�����łȂ����-1��Ԃ�
 * ---------------------------------------------- */
static int USART2_PSpacket_Recv(u8 buf[])
{
	int data, time0;
	int i;

	/* ���R�͕s������do-while���͗��p�ł��Ȃ����� */
	data = USART2_RecvByte();
	if(data == -1)	return -1;

	time0 = SystemTimer_ms_Check();
	/* �`�F�b�N�T���̃f�[�^��ǂݎ��܂Ń��[�v */
	while((data&1) == 0)
	{
		data = USART2_RecvByte();
		if(data == -1)	return -1;
		if(SystemTimer_ms_Check() - time0 > PS_RECV_TIMEOUT_MS)	return -1;
	}

	for(i = 0; i < 7; i++)
	{
		buf[i] = USART2_RecvByte();
		if(buf[i] == -1)	return i;
	}
	return i;
}

/* -------------------------------------------------
 * @�֐���	:	USART3_PSpacket_Recv
 * @�T�v		:	USART3(�d�b��)����
 * 				PS�R���g���[���̃p�P�b�g(7Byte)���󂯎��
 * @����-buf	:	�󂯎���������i�[����ϐ�
 * @�߂�l	:	��񂪎󂯎����7���A�����łȂ����-1��Ԃ�
   ---------------------------------------------- */
static int USART3_PSpacket_Recv(u8 buf[])
{
	int data, time0;
	int i;

	/* ���R�͕s������do-while���͗��p�ł��Ȃ����� */
	data = USART3_RecvByte();
	if(data == -1)	return -1;

	time0 = SystemTimer_ms_Check();
	/* �`�F�b�N�T���̃f�[�^��ǂݎ��܂Ń��[�v */
	while((data&1) == 0)
	{
		data = USART3_RecvByte();
		if(data == -1)	return -1;
		if(SystemTimer_ms_Check() - time0 > PS_RECV_TIMEOUT_MS)	return -1;
	}

	for(i = 0; i < 7; i++)
	{
		buf[i] = USART3_RecvByte();
		if(buf[i] == -1)	return i;
	}
	return i;
}

/* -------------------------------------------------
 * @�֐���		:	USART2_PSdata_Recv
 * @�T�v			:	USART2(�d�b��)����
 * 					PS�R���g���[���̃f�[�^����M����D
 * @����-psdata	:	�R���g���[���f�[�^�i�[��̕ϐ�
 * @�߂�l		:	�Ȃ�
 * ---------------------------------------------- */
void USART2_PSdata_Recv(psdata_format_t *psdata)
{
	int i;
	static int mode;
	int nBytes, sumchk = -1;
	nBytes = USART2_PSpacket_Recv(psdata->bytes);
	if(nBytes == 7)	sumchk = PSdata_CheckSum(psdata);
	if(sumchk == 1)
	{
		mode = psdata->name.Mode;
		psdata->name.Error = 0;
	}
	else
	{
		psdata->bytes[0] = psdata->bytes[1] = 0;
		for(i = 2; i < 7; i++)	psdata->bytes[i] = 0x80;
		psdata->name.LStick_X = psdata->name.LStick_Y =
		psdata->name.RStick_X = psdata->name.RStick_Y = 7;
		psdata->name.Mode = mode;
		psdata->name.Error = 1;
	}
}

/* -------------------------------------------------
 * @�֐���		:	USART3_PSdata_Recv
 * @�T�v			:	USART3(�d�b��)����
 * 					PS�R���g���[���̃f�[�^����M����D
 * @����-psdata	:	�R���g���[���f�[�^�i�[��̕ϐ�
 * @�߂�l		:	�Ȃ�
 * ---------------------------------------------- */
void USART3_PSdata_Recv(psdata_format_t *psdata)
{
	int i;
	static int mode;
	int nBytes, sumchk = -1;
	nBytes = USART3_PSpacket_Recv(psdata->bytes);
	if(nBytes == 7)	sumchk = PSdata_CheckSum(psdata);
	if(sumchk == 1)
	{
		mode = psdata->name.Mode;
		psdata->name.Error = 0;
	}
	else
	{
		psdata->bytes[0] = psdata->bytes[1] = 0;
		for(i = 2; i < 7; i++)	psdata->bytes[i] = 0x80;
		psdata->name.LStick_X = psdata->name.LStick_Y =
		psdata->name.RStick_X = psdata->name.RStick_Y = 7;
		psdata->name.Mode = mode;
		psdata->name.Error = 1;
	}
}
