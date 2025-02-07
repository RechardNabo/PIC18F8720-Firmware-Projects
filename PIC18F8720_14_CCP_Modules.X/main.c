#include <xc.h>
#include<stdio.h>
#include<string.h>
#include "Config.h"
#define _XTAL_FREQ 20000000

void Fleeking(){
    for(int x = 0 ; x < 1024 ; x++ ){
        PWM1_DUTY(x);
        LCD_20_LINE2();
        LCD_DISPLAY("PWM-RC2-CPP1: ");
        LCD_DISPLAY_DIGIT(x);
        __delay_ms(5);
    }
    for(int x = 1024 ; x > 0 ; x-- ){
        PWM1_DUTY(x);
        LCD_20_LINE2();
        LCD_DISPLAY("PWM-RC2-CPP1: ");
        LCD_DISPLAY_DIGIT(x);
        __delay_ms(5);
    }
}

void main(void) {

    ADC_Init();
    LCD_SETUP_4BIT();
    LCD_INITIALIZE_4BIT();
    PWM_SETUP();
    while(TRUE){
      
        LCD_20_LINE1();
        LCD_DISPLAY("***PIC18F8720-PWM***");
        /*LCD_20_LINE2();
        LCD_DISPLAY("PWM-RC2-CPP1: ");
        LCD_DISPLAY_DIGIT((float)ADC_Read(0));
        PWM1_DUTY((float)ADC_Read(0));*/
        Fleeking();
       
        
    }
    return;
}

