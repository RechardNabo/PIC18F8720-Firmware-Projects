#include <p18cxxx.h>
#include "Timers_lib.h"
#include <stdio.h>

#define TRUE 0x01
#define LED_PIN TRISAbits.TRISA0
#define LED PORTAbits.RA0

//==================prototyping funtions
void Timer1_Init();
void Timer1_start();
void Timer1_reset();
//==============================
void main(void)
{
 	LED_PIN = 0x00;
   	Timer1_Init();
    while (1) {                        // on répète infiniment
        Timer1_reset();                // mise à 0 du timer
        Timer1_start(1);  // attente 0,5 s
        LED = 0x00;                 // on éclaire la LED
        Timer1_reset();               // mise à 0 du timer
        Timer1_start(1);  // attente 0,5 s
        LED = 0x01;                 // on éteint la LED
    }
}





	
			
/*				
void main(void){
	LED_PIN = 0x00;
	Timer0_Init();
	
	while(TRUE){
		Timer0_start(1000);
		LED = 0x01;
		Timer0_reset();
		Timer0_start(1000);
		LED = 0x00;
		Timer0_reset();
	}
}
*/

