#include <stdlib.h>
#include <string.h>
#define CS LATF7
void SPI_MASTER_Init(){
    TRISCbits.TRISC4 = 0x01;        //SDI
    TRISCbits.TRISC3 = 0x00;        //SCK
    TRISFbits.TRISF7 = 0x00;        //SS
    TRISCbits.TRISC5 = 0x00;        //SD0
    
    CS = 0x01;
    
    SSPSTATbits.BF = 0x00;
    SSPSTATbits.UA = 0x00;
    SSPSTATbits.RW = 0x00;
    SSPSTATbits.S = 0x00;
    SSPSTATbits.P = 0x00;
    SSPSTATbits.DA = 0x00;
    SSPSTATbits.CKE = 0x01;
    SSPSTATbits.SMP = 0x00;
    
    SSPCON1bits.SSPM0 = 0x00;
    SSPCON1bits.SSPM1 = 0x00;
    SSPCON1bits.SSPM2 = 0x01;
    SSPCON1bits.SSPM3 = 0x00;
    
    PIR1bits.SSPIF = 0x00;
    ADCON0bits.ADON = 0x00;
    
    ADCON1bits.PCFG0 = 0x01;
    ADCON1bits.PCFG1 = 0x01;
    ADCON1bits.PCFG2 = 0x01;
    ADCON1bits.PCFG3 = 0x01;
    
    
}

void SPI_SLAVE_Init(){
    TRISCbits.TRISC4 = 0x01;        //SDI
    TRISCbits.TRISC3 = 0x01;        //SCK
    TRISFbits.TRISF7 = 0x01;        //SS
    TRISCbits.TRISC5 = 0x00;        //SD0
    
    
    CS = 0x01;
    
    SSPSTATbits.UA = 0x00;
    SSPSTATbits.RW = 0x00;
    SSPSTATbits.S = 0x00;
    SSPSTATbits.P = 0x00;
    SSPSTATbits.DA = 0x00;
    SSPSTATbits.CKE = 0x01;
    SSPSTATbits.SMP = 0x00;
    
    SSPCON1bits.SSPM0 = 0x00;
    SSPCON1bits.SSPM1 = 0x01;
    SSPCON1bits.SSPM2 = 0x00;
    SSPCON1bits.SSPM3 = 0x00;
    SSPCON1bits.CKP = 0x01;
    SSPCON1bits.SSPEN = 0x01;
    SSPCON1bits.SSPOV = 0x00;
    SSPCON1bits.WCOL = 0x00;
    
    PIR1bits.SSPIF = 0x00;
    ADCON0bits.ADON = 0x00;
    
    ADCON1bits.PCFG0 = 0x01;
    ADCON1bits.PCFG1 = 0x01;
    ADCON1bits.PCFG2 = 0x01;
    ADCON1bits.PCFG3 = 0x01;
}

void SPI_WRITE(unsigned char data){
    unsigned char data_flush;
    SSPBUF =  data;
    while(!SSPSTATbits.BF);
    SSPSTATbits.BF = 0x00;
    data_flush = SSPBUF;
}

unsigned char SPI_READ(){
    SSPBUF =  0xFF;
    while(!SSPSTATbits.BF);
    SSPSTATbits.BF = 0x00;
    return (SSPBUF);

}