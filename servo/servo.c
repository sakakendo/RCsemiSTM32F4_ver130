/***************************************************************************
 *	@�t�@�C����		:	motor.c
 *	@�T�v		:	DIGITAL-IO�|�[�g�Ń��[�^�𐧌䂷�邽�߂�PWM�������Ɠ�����s���D
 *					�W���̃��[�^�h���C�o���g�����Ƃ�z�肵�Ă���D
 *					�܂��C���ԑ҂��֐���V�X�e���^�C�}���񋟂��Ă���D
 *	@�o�[�W����		:	1.2.0
 *	@�J����		:	�L�l�N�g
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/

#include <stm32f4xx.h>
#include "digitalIO.h"
#include "servo.h"
#include "lcd.h"		// **���ꂪ�K�v
#include "timer.h"		// **���ꂪ�K�v
#include "xprintf.h"

int irq=0;

/* ��Βl�����߂� */
//motor.h��include����Ă���͂�������ꉞ
#ifndef ABS_VAL
#define ABS_VAL(val) ((val) < 0 ? -(val) : (val))
#endif //ABS_VAL

//debug �pxprintf
#define printd(fmt,...) xprintf("%s %d %s",__func__,__LINE__,fmt)
_servo_status_t gServo_status[3]={};

void Servo_Drive(short high,short low){
	u8 port=0,ch=0;
	gServo_status[port].high[ch]=high;
	gServo_status[port].low[ch] =low;
}

void TIM2_CMT_Init(){
	//1kHz = 1ms�ł̊�����
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC=100-1;
	TIM2->ARR=840-1;
	TIM2->CNT=0;
	TIM2->SR=0;
    TIM2->DIER=TIM_DIER_UIE;
	TIM2->CR1|=TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(){
	int port=0,pin=0;
	TIM2->SR=0;
	//static int i=0;
	//i++;
/*	for(port=0;port<3;port++){
		for(pin=0;pin<8;pin++){
		}
	}
*/
	gServo_status[port].cnt[pin]++;
	if( 0< gServo_status[port].cnt[pin] && gServo_status[port].cnt[pin] <=gServo_status[port].high[pin]){
		DIO_OutputPin(port,pin,1);
	}else if( gServo_status[port].high[pin] <= gServo_status[port].cnt[pin]
	                 && gServo_status[port].cnt[pin] <=gServo_status[port].high[pin] +gServo_status[port].low[pin] ){
		DIO_OutputPin(port,pin,0);
	}else if( 0< gServo_status[port].cnt[pin] && gServo_status[port].cnt[pin] <=gServo_status[port].high[pin]){
		gServo_status[port].cnt[pin]=0;
		DIO_OutputPin(port,pin,0);
	}
}
