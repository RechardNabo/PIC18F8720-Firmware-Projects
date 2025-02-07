#include <stdlib.h>
#include <stdio.h>

short data;

void I2C_SLAVE_Init(short address){
    
    SSPSTATbits.BF = 0x00;
    SSPSTATbits.UA = 0x00;
    SSPSTATbits.RW = 0x00;
    SSPSTATbits.S = 0x00;
    SSPSTATbits.P = 0x01;
    SSPSTATbits.DA = 0x00;
    SSPSTATbits.CKE = 0x01;
    SSPSTATbits.SMP = 0x00;
    
    SSPADD = address;
    SSPCON1bits.SSPM0 = 0x00;
    SSPCON1bits.SSPM1 = 0x01;
    SSPCON1bits.SSPM2 = 0x01;
    SSPCON1bits.SSPM3 = 0x00;
    SSPCON1bits.CKP = 0x01;
    SSPCON1bits.SSPEN = 0x01;
    SSPCON1bits.SSPOV = 0x00;
    SSPCON1bits.WCOL = 0x00;
    
    SSPCON2bits.SEN = 0x001;
    SSPCON2bits.RSEN = 0x00;
    SSPCON2bits.PEN = 0x00;
    SSPCON2bits.RCEN = 0x00;
    SSPCON2bits.ACKEN = 0x00;
    SSPCON2bits.ACKDT = 0x00;
    SSPCON2bits.ACKSTAT = 0x00;
    SSPCON2bits.GCEN = 0x00;
    
    INTCONbits.GIE = 0x01;
    INTCONbits.PEIE = 0x01;
    SSPIF = 0x00;
    SSPIE = 0x01;
}

short __interrupt I2C_Slave_Read(){
    
    if(SSPIF == 1){
       SSPCON1bits.CKP = 0;
       
       if ((SSPCON1bits.SSPOV) || (SSPCON1bits.WCOL)){
             data = SSPBUF;            // Read the previous value to clear the buffer
             SSPCON1bits.SSPOV = 0; // Clear the overflow flag
             SSPCON1bits.WCOL = 0;   // Clear the collision bit
             SSPCON1bits.CKP = 1;
       }

      if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) 
       {
           data = SSPBUF;
           while(!BF);
           SSPCON1bits.CKP = 1;
           SSPM3 = 0;
       }
       else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW)
       {
           data = SSPBUF;
           BF = 0;
           SSPBUF = PORTB ;
           SSPCON1bits.CKP = 1;
           while(SSPSTATbits.BF);
       }
       
       SSPIF = 0;
    }
}

short Data(){
    return data;
}