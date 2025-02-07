#include <p18cxxx.h>
#define _XTAL_FREQ 640000000
#include <stdio.h>
#include <delays.h>

#define TRUE 0x01
#define LED_PORT TRISAbits.TRISA0
#define Button_PORT TRISEbits.TRISE0

#define LED PORTAbits.RA0 
#define BUTTON PORTEbits.RE0
 
void main(void){
	LED_PORT = 0x00;
	Button_PORT = 0x01;
	LED = 0x00;
	
	while(TRUE){
		if(BUTTON == 0x01){LED = 0X01;}
		if(BUTTON == 0x00){LED = 0x00;}
		Delay10TCYx(255);
	}
}