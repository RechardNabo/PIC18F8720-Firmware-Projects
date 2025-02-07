#include <p18cxxx.h>
#include <stdio.h>
#include <delays.h>

#define TRUE 0x01
#define TIME 255
#define LED_PORT1 TRISEbits.TRISE0
#define LED_PORT2 TRISEbits.TRISE1
#define LED_PORT3 TRISEbits.TRISE2
#define LED_PORT4 TRISEbits.TRISE3

#define LED1 PORTEbits.RE0
#define LED2 PORTEbits.RE1
#define LED3 PORTEbits.RE2
#define LED4 PORTEbits.RE3
 
void main(void){
	LED_PORT1 = 0x00;
	LED_PORT2 = 0x00;
	LED_PORT3 = 0x00;
	LED_PORT4 = 0x00;
	
	while(TRUE){
		LED1 = 0x01;
		LED2 = 0x00;
		LED3 = 0x00;
		LED4 = 0x00;
		Delay10TCYx(TIME);
		LED1 = 0x00;
		LED2 = 0x01;
		LED3 = 0x00;
		LED4 = 0x00;
		Delay10TCYx(TIME);
		LED1 = 0x00;
		LED2 = 0x00;
		LED3 = 0x01;
		LED4 = 0x00;
		Delay10TCYx(TIME);
		LED1 = 0x00;
		LED2 = 0x00;
		LED3 = 0x00;
		LED4 = 0x01;
		Delay10TCYx(TIME);
	}
}