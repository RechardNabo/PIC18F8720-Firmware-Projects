#include <p18cxxx.h>
#include <stdio.h>
#include <stdlib.h>
#define EN_PINS TRISF
#define DISPLAY_PINS PORTF
#define ANODE 'A'
#define CATHODE 'C'

void Seg_Init(){
	EN_PINS = 0x00;
}void Seg_Init();

void Seg_Cath_Display(int num){
		
		switch(num){
		//hgfe dcba
		case 0x00:
		DISPLAY_PINS = 0b00111111;
		break;
		
		case 0x01:
		DISPLAY_PINS = 0b00000110;
		break;
		
		case 0x02:
		DISPLAY_PINS = 0b01011011;
		break;
		
		case 0x03:
		DISPLAY_PINS = 0b11001111;
		break;
		
		case 0x04:
		DISPLAY_PINS = 0b11100110;
		break;
		
		case 0x05:
		DISPLAY_PINS = 0b11101101;
		break;
		
		case 0x06:
		DISPLAY_PINS = 0b11111101;
		break;
		
		case 0x07:
		DISPLAY_PINS = 0b00000111;
		break;
		
		case 0x08:
		DISPLAY_PINS = 0b11111111;
		break;
		
		case 0x09:
		DISPLAY_PINS = 0b11101111;
		break;
		
		case 0x0A:
		DISPLAY_PINS = 0b11110111;
		break;
		
		case 0x0B:
		DISPLAY_PINS = 0b11111100;
		break;
		
		case 0x0C:
		DISPLAY_PINS = 0b10111001;
		break;
		
		case 0x0D:
		DISPLAY_PINS = 0b11011110;
		break;
		
		case 0x0E:
		DISPLAY_PINS = 0b11111001;
		break;
		
		case 0x0F:
		DISPLAY_PINS = 0b11110001;
		break;
		
		default:
		break;
		}	
	}
void Seg_Ano_Display(int num){
		switch(num){
		//hgfe dcba
		case 0x00:
		DISPLAY_PINS = 0b11000000;
		break;
		
		case 0x01:
		DISPLAY_PINS = 0b111111001;
		break;
		
		case 0x02:
		DISPLAY_PINS = 0b01011011;
		break;
		
		case 0x03:
		DISPLAY_PINS = 0b00110000;
		break;
		
		case 0x04:
		DISPLAY_PINS = 0b00011001;
		break;
		
		case 0x05:
		DISPLAY_PINS = 0b00010010;
		break;
		
		case 0x06:
		DISPLAY_PINS = 0b00000010;
		break;
		
		case 0x07:
		DISPLAY_PINS = 0b01111000;
		break;
		
		case 0x08:
		DISPLAY_PINS = 0b00000000;
		break;
		
		case 0x09:
		DISPLAY_PINS = 0b00010000;
		break;
		
		case 0x0A:
		DISPLAY_PINS = 0b00001000;
		break;
		
		case 0x0B:
		DISPLAY_PINS = 0b00000011;
		break;
		
		case 0x0C:
		DISPLAY_PINS = 0b01000110;
		break;
		
		case 0x0D:
		DISPLAY_PINS = 0b00100001;
		break;
		
		case 0x0E:
		DISPLAY_PINS = 0b00000110;
		break;
		
		case 0x0F:
		DISPLAY_PINS = 0b00001110;
		break;
		
		default:
		break;
		}		
}void Seg_Ano_Display();

void Up_count(unsigned char type){
	int x = 0x00;
	if(type == CATHODE){
		while(x!=0x10){
		if(x > 0x0F){x=0x00;}
		Seg_Cath_Display(x);
		Delay10TCYx(10);
		x++;
		}
	if(type == ANODE){
		while(x!=0x10){
		if(x > 0x0F){x=0x00;}
		Seg_Ano_Display(x);
		Delay10TCYx(10);
		x++;
		}
 	 }
   }
}void Up_count(); 
 
void Down_count(unsigned char type){
	int x = 0x0F;
	if(type == CATHODE){
		for(x ; x>0x00; x-=+0x01){
		if(x < 0x00){x=0x0F;}
		Seg_Cath_Display(x);
		Delay10TCYx(10);
		}
	if(type == ANODE){
		for(x ; x>0x00; x-=+0x01){
		if(x < 0x00){x=0x0F;}
		Seg_Ano_Display(x);
		Delay10TCYx(2);
		}
	}
 }
}void Down_count();
