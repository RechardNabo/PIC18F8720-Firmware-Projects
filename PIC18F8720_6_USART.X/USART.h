#include <xc.h>  
#define _XTAL_FREQ 20000000
#define TX_PIN TRISCbits.TRISC6
#define RX_PIN TRISCbits.TRISC7

float SPBRG_Value(int baud_rate){
    float SPBRG_value = 0;
    SPBRG_value = (((float)_XTAL_FREQ/((16)*(float)baud_rate)) - 1);
    return (SPBRG_value);
    
}

void USART_Initialize(int baud_rate){
    TX_PIN = 0;
    RX_PIN = 1;
    
    SPBRG1 = (unsigned char)SPBRG_Value(baud_rate);
    
    TXSTA1bits.TXEN1 = 1;
    TXSTA1bits.TX91 = 0;
    TXSTA1bits.SYNC1 = 0;
    TXSTA1bits.CSRC1 = 1;
    TXSTA1bits.TX9D1 = 0;
    TXSTA1bits.TRMT1 =0;
    TXSTA1bits.BRGH1 = 1;

    
    RCSTA1bits.SPEN1 = 1;
    RCSTA1bits.CREN1 = 1;
    RCSTA1bits.RX91 = 0;
    RCSTA1bits.RX9D1 = 0;
    RCSTA1bits.OERR1 =0;
    RCSTA1bits.FERR1 = 0;
    RCSTA1bits.ADDEN1 = 0;
    RCSTA1bits.SREN1 = 0;
    
    PIE1bits.TX1IE = 1;
    PIE1bits.RC1IE = 1;
    PIR1bits.TX1IF = 0;
    PIR1bits.RC1IF = 0;
    INTCON1bits.GIE = 1;
    INTCON1bits.PEIE = 1;
}
void USART_Flush(){
    
    char flush;
    while(PIR1bits.RC1IF){
        flush = RCREG1;
    }
    while(!TXSTA1bits.TRMT1);    
}
void USART_Transmit(unsigned char data){
    USART_Flush();
    while(!PIR1bits.TX1IF);
    TXREG = data;
    PIR1bits.TX1IF = 0;
}

void USART_Transmit_String(unsigned char *data){
    USART_Flush();
    TXSTA1bits.SYNC1 = 0;
    while(*data){
        USART_Transmit(*data++);
    }
    
}
char USART_Receive(){
    USART_Flush();
    RCSTA1bits.SREN1 = 1;
    uint8_t _9BIT, data = 0x00;
    TXREG = 0;
    _9BIT = RCSTA1bits.RX9D1;
    if(RCSTA1bits.OERR1){ // check for Error
        RCSTA1bits.CREN1 = 0; //If error -> Reset 
        RCSTA1bits.CREN1 = 1; //If error -> Reset 
    }
    if(_9BIT == 0){
        while(!PIR1bits.RC1IF);
        PIR1bits.RC1IF = 0;
        __delay_us(1);
        data = RCREG1;
    }
    return (char)data;
}

char * USART_Receive_String(){
    USART_Flush();
    TXSTA1bits.SYNC1 = 0;
    char i = 0;
    char data;
    char * full_data;
    while((data = USART_Receive()) != '\0'){
        full_data[i++] = data;
    }
    return full_data;
}