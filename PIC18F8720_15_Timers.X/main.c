
// PIC18F8720 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator with PLL enabled; clock frequency = (4 x FOSC))
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config BORV = 25        // Brown-out Reset Voltage bits (VBOR set to 2.5V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 1        // Watchdog Timer Postscale Select bits (1:1)

// CONFIG3L
#pragma config MODE = MC        // Processor Mode Select bits (Microcontroller mode)
#pragma config WAIT = OFF       // External Bus Data Wait Enable bit (Wait selections unavailable for table reads and table writes)

// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = OFF       // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Low-Voltage ICSP Enable bit (Low-voltage ICSP disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)
#pragma config CP4 = OFF        // Code Protection bit (Block 4 (010000-013FFFh) not code-protected)
#pragma config CP5 = OFF        // Code Protection bit (Block 5 (014000-017FFFh) not code-protected)
#pragma config CP6 = OFF        // Code Protection bit (Block 6 (018000-01BFFFh) not code-protected)
#pragma config CP7 = OFF        // Code Protection bit (Block 7 (01C000-01FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)
#pragma config WRT4 = OFF       // Write Protection bit (Block 4 (010000-013FFFh) not write-protected)
#pragma config WRT5 = OFF       // Write Protection bit (Block 5 (014000-017FFFh) not write-protected)
#pragma config WRT6 = OFF       // Write Protection bit (Block 6 (018000-01BFFFh) not write-protected)
#pragma config WRT7 = OFF       // Write Protection bit (Block 7 (01C000-01FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR4 = OFF      // Table Read Protection bit (Block 4 (010000-013FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR5 = OFF      // Table Read Protection bit (Block 5 (014000-017FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR6 = OFF      // Table Read Protection bit (Block 6 (018000-01BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR7 = OFF      // Table Read Protection bit (Block 7 (01C000-01FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include "LCD.h"

#define _XTAL_FREQ 20000000
#define TRUE 0x01
#define FALSE 0x00
#define TIMER_DELAY 100

#define LED_PIN1 TRISDbits.RD0
#define LED_PIN2 TRISDbits.RD1
#define LED_PIN3 TRISDbits.RD2
#define LED_PIN4 TRISDbits.RD3
#define LED_PIN5 TRISDbits.RD4
#define LED_PIN6 TRISDbits.RD5
#define LED_PIN7 TRISDbits.RD6
#define LED_PIN8 TRISDbits.RD7

#define LED8 LATDbits.LD7
#define LED7 LATDbits.LD6

void Timer0_Initialize_10mS_();
void Timer1_Initialize_1_S();
void __interrupt ISR();
volatile unsigned int Timer_1_Counter = 0;
volatile int Interrupt = 0;
void main(void) {
    char msg[20];
    char msg2[20];
    LCD_SETUP_4BIT();
    LCD_INITIALIZE_4BIT();
    Timer0_Initialize_10mS_();
    Timer1_Initialize_1_S();
    while(TRUE){

        LCD_20_LINE1();
        LCD_DISPLAY("PIC18 TIMERS");
        LCD_20_LINE2();
        sprintf(msg, "Timer 1 flag : %d",Interrupt);
        LCD_DISPLAY(msg);
    }
    return;
}

void Timer0_Initialize_10mS_(){
    T0CONbits.T0PS0 = 0;
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS2 = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0SE = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.T08BIT =1;
    T0CONbits.TMR0ON = 1;
    
    TMR0L = 0;
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE =1;
    LED_PIN8 = 0;
}

void Timer1_Initialize_1_S(){
    T1CONbits.TMR1ON = 1;
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1CS =0;
    T1CONbits.SOSCEN = 0;
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1CKPS1 =0;
    T1CONbits.T1SYNC = 0;
    T1CONbits.T1RD16 = 1;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE =1;
    INTCONbits.GIE = 1;
    
    TMR1H = 0x3C;
    TMR1L = 0xB0;
    LED_PIN7 = 0;
}

void __interrupt ISR(){
    
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        TMR0L = 0;
        LED8 ^=1;
    }
    if(PIR1bits.TMR1IF){
        PIR1bits.TMR1IF = 0;
        Timer_1_Counter = Timer_1_Counter+1;
        if(Timer_1_Counter >= 100){
            Timer_1_Counter =0;
            LED7 ^=1;
            Interrupt ^= 1;
        }
    }
}

