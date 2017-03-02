/***************************************************************************
 *	@ファイル名		:	servo.h
 *	@概要		:	DIGITAL-IOポートでモータを制御するためのPFM初期化と動作を行う．
 *	@バージョン		:	1.2.0
 *	@開発者			:	saka
 *	@使用環境		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/
typedef struct
{
	short high[8];
	short low[8];
	short cnt[8];
} _servo_status_t;

/* 関数プロトタイプ宣言	===================================================== */
/* -------------------------------------------------
 * @関数名		:	Motor_Drive
 * @概要			:	モータポートからPFMを出力する、
 * 				:	high,low[ns]を指定(0,0)に出力
 * @戻り値		:	なし
 * ---------------------------------------------- */
void Servo_Drive(short high,short low);

//こんな関数必要ないでしょ
//void ServoDriver_Init(u16 motors);
