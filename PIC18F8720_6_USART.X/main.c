#include <xc.h>
#include<stdio.h>
#include<string.h>
#include "USART.h"
#include "Config.h"
#define _XTAL_FREQ 20000000

void main() {

    TRISDbits.TRISD4 = 0;
    USART_Initialize(9600);
    while (TRUE) {

        PORTDbits.RD4 = 1;
        __delay_ms(1000);
        PORTDbits.RD4 = 0;
        USART_Transmit('A');
        __delay_ms(1000);
    }
}