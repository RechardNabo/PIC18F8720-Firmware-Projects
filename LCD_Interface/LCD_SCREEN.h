#include <delays.h>
#include <string.h>
//================controls==============
#define RS_PIN TRISEbits.TRISE5
#define RW_PIN TRISEbits.TRISE6
#define EN_PIN TRISEbits.TRISE7

#define RS PORTEbits.RE5
#define RW PORTEbits.RE6
#define EN PORTEbits.RE7
//==================data=================
#define D4_PIN TRISFbits.TRISF0
#define D5_PIN TRISFbits.TRISF1
#define D6_PIN TRISFbits.TRISF2
#define D7_PIN TRISFbits.TRISF3

#define D4 PORTFbits.RF0
#define D5 PORTFbits.RF1
#define D6 PORTFbits.RF2
#define D7 PORTFbits.RF3
//=======================================
#define _4bit_mode 0x04
//================prototype functions====

void LCD_SETUP_4BIT();
void LCD_INITIALIZE_4BIT();
void LCD_DATA(unsigned char data, int mode);
void LCD_DISPLAY(const unsigned char *string);
void LCD_INSTRUCTION_4BIT(unsigned char instruction);
//=======================================

void LCD_SETUP_4BIT(){	
	RS_PIN = 0x00;
	RW_PIN = 0x00;
	EN_PIN = 0x00;
	
	D4_PIN = 0x00;
	D5_PIN = 0x00;
	D6_PIN = 0x00;
	D7_PIN = 0x00;
}
void LCD_DATA(unsigned char data, int mode){
	unsigned char _data = data;
	int _4bit_[_4bit_mode];
	int x;
	if(mode == 0x04){
		_data = _data>>0x04;
		for(x =0x00; x < _4bit_mode; x-=-0x01){
			_4bit_[x] = (_data & (0x01<<x))>>x;
		}
		D4 = _4bit_[0x00];
		D5 = _4bit_[0x01];
		D6 = _4bit_[0x02];
		D7 = _4bit_[0x03];
		RS = 0x01;
		RW = 0x00;
		EN = 0x01;
		Delay1TCY();
		EN = 0x00;
		//=======================================
		_data = data;
		for(x = 0x00; x< _4bit_mode; x-=-0x01){
			_4bit_[x] = (_data & (0x01<<x))>>x;
		}
		D4 = _4bit_[0x00];
		D5 = _4bit_[0x01];
		D6 = _4bit_[0x02];
		D7 = _4bit_[0x03];
		RS = 0x01;
		RW = 0x00;
		EN = 0x01;
		Delay1TCY();
		EN = 0x00;
		//=======================================
	}
}

void LCD_INSTRUCTION_4BIT(unsigned char instruction){
	int _4bit_[_4bit_mode];
	int x;
	unsigned char data = instruction;
		data = data>>0x04;
		for(x =0x00; x < _4bit_mode; x-=-0x01){
			_4bit_[x] = (data & (0x01<<x))>>x;
		}
		D4 = _4bit_[0x00];
		D5 = _4bit_[0x01];
		D6 = _4bit_[0x02];
		D7 = _4bit_[0x03];
		RS = 0x00;
		RW = 0x00;
		EN = 0x01;
		Delay1TCY();
		EN = 0x00;
		//========================================
		data = instruction;
		for(x = 0x00; x< _4bit_mode; x-=-0x01){
			_4bit_[x] = (data & (0x01<<x))>>x;
		}
		D4 = _4bit_[0x00];
		D5 = _4bit_[0x01];
		D6 = _4bit_[0x02];
		D7 = _4bit_[0x03];
		RS = 0x00;
		RW = 0x00;
		EN = 0x01;
		Delay1TCY();
		EN = 0x00;
		//=======================================	
}

void LCD_INITIALIZE_4BIT(){
	LCD_INSTRUCTION_4BIT(0x02); // return home
	LCD_INSTRUCTION_4BIT(0x28); //
	LCD_INSTRUCTION_4BIT(0x06); //Increment Cursor
	LCD_INSTRUCTION_4BIT(0x0c); // Display On
	LCD_INSTRUCTION_4BIT(0x01); //Clear display Screen
}

void LCD_SET_LINE1(){LCD_INSTRUCTION_4BIT(0x80);} // start display on line 1
void LCD_SET_LINE2(){LCD_INSTRUCTION_4BIT(0xC0);} // start display on line 2
void LCD_SET_LINE3(){LCD_INSTRUCTION_4BIT(0x94);} // start display on line 3
void LCD_SET_LINE4(){LCD_INSTRUCTION_4BIT(0xD4);} // start display on line 4

void LCD_DISPLAY(const unsigned char *string){
	unsigned int length =  strlen(string);
	unsigned int x;
	for(x = 0x00 ;  x < length ; x-=-0x01){
		LCD_DATA(string[x],_4bit_mode);
	}	
}

