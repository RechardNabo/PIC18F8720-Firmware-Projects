#include <p18f8722.h>
#include <stdlib.h>
#include <timers.h>
#include <pwm.h>

#define TRUE 0x01

void main(void){
	OpenTimer2( TIMER_INT_OFF &
				T2_PS_1_1 &
				T2_POST_1_16 );
	
	OpenPWM1(0xff);
	SetDCPWM1(0);
	SetOutputPWM1 (SINGLE_OUT, PWM_MODE_1);
	while(TRUE){
	
	}
}