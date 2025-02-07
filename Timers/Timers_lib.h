#include <timers.h>

void Timer0_Init(){
	// configure timer0
	OpenTimer0(TIMER_INT_OFF &	
				T0_16BIT &		
				T0_SOURCE_INT &	
				T0_PS_1_256		
				);
}

void Timer1_Init(){
	OpenTimer1( TIMER_INT_ON &
				T1_16BIT_RW &
				T1_SOURCE_INT &
				T1_PS_1_8 &
				T1_OSC1EN_OFF &
				T1_SYNC_EXT_OFF );
}
void Timer2_Init(){
	OpenTimer2( TIMER_INT_OFF &
				T2_PS_1_1 &
				T2_POST_1_16 );
}

void Timer3_Init(){
	OpenTimer3( TIMER_INT_ON &
				T3_16BIT_RW &
				T3_SOURCE_INT &
				T3_PS_1_8 &
				T3_SYNC_EXT_OFF );
}

void Timer4_Init(){
	OpenTimer4( TIMER_INT_OFF &
				T4_PS_1_16 &
				T4_POST_1_16 );
}

void Timer0_start(unsigned int interval){
	switch(interval){
		case 16:
		while(ReadTimer0()< 733);
			break;
			
		case 32:
		while(ReadTimer0()< 1465);
			break;
		
		case 63:
		while(ReadTimer0() < 2930);
			break;
			
		case 125:
		while(ReadTimer0() < 5860);
			break;
			
		case 250:
		while(ReadTimer0() < 11719);
			break;
				
		case 500:
		while(ReadTimer0()< 23438 );
			break;
			
		case 1000:
		while(ReadTimer0() < 46876);
			break;
		
		case 1500:
		while(ReadTimer0()< 70314);
			break;
			
		case 2000:
		while(ReadTimer0()< 93752);
			break;
			
		default:
			break;
	}
}

void Timer1_start(unsigned int interval){
	switch(interval){
		case 1:
		while (ReadTimer1() < 65438);
			break;
	}
}
void Timer0_reset(){WriteTimer0(0);}
void Timer1_reset(){WriteTimer1(0);}
void Timer2_reset(){WriteTimer2(0);}
void Timer3_reset(){WriteTimer3(0);}
void Timer4_reset(){WriteTimer4(0);}
/*
void Timer0_stop(){CloseTimer0();}
void Timer1_stop(){CloseTimer1();}
void Timer2_stop(){CloseTimer2();}
void Timer3_stop(){CloseTimer3();}
void Timer4_stop(){CloseTimer4();}*/