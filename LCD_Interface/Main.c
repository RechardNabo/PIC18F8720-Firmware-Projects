#include <p18cxxx.h>
#include "LCD_SCREEN.h"
#include <stdio.h>
#include <delays.h>

#define TRUE 0x01
#define PIN1 TRISEbits.TRISE0
#define LED PORTEbits.RE0

//====== functions prototypes================
void LCD_SET_LINE1();
void LCD_SETUP_4BIT();
void LCD_INITIALIZE_4BIT();
//===========================================


void main(void){
	LCD_SETUP_4BIT();
	LCD_INITIALIZE_4BIT();
	
	while(TRUE){
		LCD_SET_LINE1();
		LCD_DISPLAY("Hello World");
	}
}
