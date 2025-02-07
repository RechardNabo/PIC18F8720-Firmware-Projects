#include <p18f8722.h>
#include <stdlib.h>
#include "ADC_Selector.h"

#define TRUE 0x01
#define LED_PIN TRISEbits.TRISE0
#define LED PORTEbits.RE0

//================prototype functions=====
void ANA0_Init();
unsigned int Read_Analog();
//========================================

void main(void){
	LED_PIN =0x00;
	ANA0_Init(1);
		
	while(TRUE){
	if(Read_Analog() > 0x00){
		LED = 0x01;
	}
  }	
}