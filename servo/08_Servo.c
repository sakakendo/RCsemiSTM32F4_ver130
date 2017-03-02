#include "stm32f4xx.h"
#include "digitalIO.h"
#include "motor.h"
#include "timer.h"		// **これが必要
#include "servo.h"


#define __08_SERVO__
#ifdef __08_SERVO__

//debug用変数

//関数に入った回数をカウント
//irq		servo.c :: TIM2_IRQHandler

//main_g	main.c :: main()
//while_g	main.c :: while(1)
//pinの状態をglobalに
//pin_state	servo.c :: TIM2_IRQHandler
extern int irq,pin_state;
int main_g=0,while_g=0;

int main(){
	main_g++;
 	SystemCoreClockUpdate();	// **システムクロックを初期化する
	TIM2_CMT_Init();
	DIO0_Init(0xFF, DIO_MODE_OUT);	// **モータポートとして使用するピンを出力に設定しておく
	while_g++;
	while(1)
	{
		Servo_Drive(20,20);
	}
	return 0;
}

#endif //__08_SERVO__
