#include <xc.h>
#include <stdio.h>

void ADC_Init();
int ADC_Read(int channel);

void ADC_Init(){
     ADCON0bits.ADON = 0x01;
    ADCON0bits.CHS0 = 0x00;
    ADCON0bits.CHS1 = 0x00;
    ADCON0bits.CHS2 = 0x00;
    ADCON0bits.CHS3 = 0x00;
    
    ADCON1bits.PCFG0 = 0x01;
    ADCON1bits.PCFG1 = 0x01;
    ADCON1bits.PCFG2 = 0x01;
    ADCON1bits.PCFG3 = 0x00;
    ADCON1bits.VCFG0 = 0x00;
    ADCON1bits.VCFG1 = 0x00;
    
    ADCON2bits.ADFM = 0x01;
    ADCON2bits.ADCS0 = 0;
    ADCON2bits.ADCS1 = 1;
    ADCON2bits.ADCS2 = 0;
    ADRESH = 0x00;
    ADRESL = 0x00;
}


int ADC_Read(int channel){
    int digital;
    ADCON0 =(ADCON0 & 0b11000011)|((channel<<2) & 0b00111100); /*channel 0 is selected i.e (CHS3CHS2CHS1CHS0=0000)
    and ADC is disabled i.e ADON=0*/
    ADCON0 |= ((1<<ADON)|(1<<GO)); /*Enable ADC and start conversion*/
    while(ADCON0bits.GO_nDONE==1); /*wait for End of conversion i.e. Go/done'=0 conversion completed*/
    digital = (ADRESH*256) | (ADRESL); /*Combine 8-bit LSB and 2-bit MSB*/
    return(digital);
}

unsigned int ADC_Read_2(unsigned char channel){
  ADCON0 &= 0x11000101; //Clearing the Channel Selection Bits
  ADCON0 |= channel<<3; //Setting the required Bits
  __delay_ms(2); //Acquisition time to charge hold capacitor
  GO_nDONE = 1; //Initializes A/D Conversion
  while(GO_nDONE); //Wait for A/D Conversion to complete
  return ((ADRESH<<8)+ADRESL); //Returns Result
}
//=================================================================================
void ADC_INIT(){
   ADCON0 = 0x41;
   ADCON1 = 0xC0;
}

unsigned int ADC_READ(unsigned char channel){
   if(channel > 7)
     return 0; 

   ADCON0 &= 0xC5;
   ADCON0 |= channel<<3;
   __delay_ms(2);
   GO_nDONE = 1;
   while(GO_nDONE);
   return ((ADRESH<<8)+ADRESL);
}