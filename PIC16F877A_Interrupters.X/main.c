// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 20000000

void interrupt ISR(void){
    if(INTCONbits.INTF == 0x01){
        PORTDbits.RD0 = ~ PORTDbits.RD0;
        INTCONbits.INTF = 0x00;
    }

}
void main(void) {
    
 //===========================[Digital outputs and input interrupters]================
    TRISAbits.TRISA0 = 0x00;        //led blinking 100 ms
    TRISDbits.TRISD0 = 0x00;        //interrupt output
    TRISBbits.TRISB0 = 0x01;        //Interrupt input
    PORTDbits.RD0 = 0x00;
    
//===========================[configure registers]====================================
    
    OPTION_REGbits.INTEDG = 0x00;   //[o falling edge and 1 is rising edge]
    OPTION_REGbits.nRBPU = 0x00;
    INTCONbits.GIE = 0x01;          //enable global interrupter
    INTCONbits.PEIE = 0x01;         //enable peripheral interrupters
    INTCONbits.INTE = 0x01;         //enable interrupter
    
       
    while(1){
        PORTAbits.RA0 = 0x00;
        __delay_ms(100);
        PORTAbits.RA0 = 0x01;
        __delay_ms(100);
    }
    return;
}
