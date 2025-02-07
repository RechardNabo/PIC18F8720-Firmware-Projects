#include <p18cxxx.h>
#include <stdio.h>
#include <delays.h>
#define TRUE 0x01
#define LED_PORT TRISAbits.TRISA0 
#define LED PORTAbits.RA0
 
void main(void){
	LED_PORT = 0x00;
	while(TRUE){
		LED = 0x01;
		Delay10KTCYx(100);
		LED = 0x00;
		Delay10KTCYx(100);
	}
}