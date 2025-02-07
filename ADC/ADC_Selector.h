#include <delays.h>
#include <adc.h>

int result = 0x00;

//=====prototypr function=========
void ConvertADC();
int ReadADC();
void CloseADC();
//=================================

void ANA0_Init(unsigned int select){
	switch(select){
		case 1:
		OpenADC( ADC_FOSC_32 &
			ADC_RIGHT_JUST &
			ADC_12_TAD&
			ADC_1ANA,
			ADC_CH1 &
			ADC_INT_OFF&
			ADC_VREFPLUS_VDD,0);
		SetChanADC( ADC_CH0 );
			break;
			
		case 2:
		OpenADC( ADC_FOSC_32 &
			ADC_RIGHT_JUST &
			ADC_12_TAD&
			ADC_2ANA,
			ADC_CH2 &
			ADC_INT_OFF&
			ADC_VREFPLUS_VDD,0);
		SetChanADC( ADC_CH2 );
			
		case 3:
		OpenADC( ADC_FOSC_32 &
			ADC_RIGHT_JUST &
			ADC_12_TAD&
			ADC_3ANA,
			ADC_CH3 &
			ADC_INT_OFF&
			ADC_VREFPLUS_VDD,0);
		SetChanADC( ADC_CH3 );
			
		case 4:
		OpenADC( ADC_FOSC_32 &
			ADC_RIGHT_JUST &
			ADC_12_TAD&
			ADC_4ANA,
			ADC_CH4 &
			ADC_INT_OFF&
			ADC_VREFPLUS_VDD,0);
		SetChanADC( ADC_CH4 );
			
		case 5:
		OpenADC( ADC_FOSC_32 &
			ADC_RIGHT_JUST &
			ADC_12_TAD&
			ADC_5ANA,
			ADC_CH5 &
			ADC_INT_OFF&
			ADC_VREFPLUS_VDD,0);
		SetChanADC( ADC_CH5 );
	}
}

unsigned int Read_Analog(){
	int unsigned result;
	ConvertADC();
	while(BusyADC());
		result = ReadADC();
		CloseADC();
	return result;
}
