#include <p18cxxx.h>
#include <delays.h>
#include <stdio.h>
#include "Seg7_lib.h"
#define TRUE 0x01
#define Digit1 TRISAbits.TRISA0
#define Digit2 TRISAbits.TRISA1
#define Control_Digit1 PORTAbits.RA0
#define Control_Digit2 PORTAbits.RA1
//==================prototype functions
void Seg_Init();
void Down_count();
void Seg_Display();
//==================

void main(void){
	Digit1 = 0x00;
	Digit2 = 0x00;
	Seg_Init();
	while(TRUE){
		Control_Digit1 = 0x00;
		Down_count('C');
		Delay10TCYx(10);
	}
}