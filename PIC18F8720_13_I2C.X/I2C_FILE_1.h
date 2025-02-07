#include <pic18.h>
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
#define SCL TRISCbits.RC3
#define SDA TRISCbits.RC4
#define OR ||
#define _XTAL_FREQ 20000000
#define I2C_WRITE_BIT 0;
#define I2C_READ_BIT 1

void I2C_Initialize(){
    SCL = 1;
    SDA = 1;
    SSPCON1bits.SSPM0 = 0;
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM2 = 0;
    SSPCON1bits.SSPM3 = 1;
    SSPCON1bits.CKP = 0;
    SSPCON1bits.SSPEN = 1;
    SSPCON1bits.SSPOV = 0;
    SSPCON1bits.WCOL = 0;
    
    SSPCON2bits.SEN = 0;
    SSPCON2bits.RSEN = 0;
    SSPCON2bits.PEN = 0;
    SSPCON2bits.RCEN = 0;
    SSPCON2bits.ACKEN = 0;
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKSTAT = 0;
    SSPCON2bits.GCEN = 0;
    
    SSPSTATbits.BF = 0;
    SSPSTATbits.UA = 0;
    SSPSTATbits.R_W = 0;
    SSPSTATbits.S =0;
    SSPSTATbits.P = 0;
    SSPSTATbits.DA = 0;
    SSPSTATbits.CKE = 0;
    SSPSTATbits.SMP =0;
    SSPADD = 11;
    
}

void I2C_Interrupt_Flag_Polling(){
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
}

void I2C_Open(){
    PIR1bits.SSPIF = 0;
    SSPCON1bits.SSPEN = 1;
}

void I2C_Close(){
    SSPCON1bits.SSPEN = 0;
}

void I2C_Start_Condition(){
    SSPCON2bits.SEN = 1;
    I2C_Interrupt_Flag_Polling();
}

void I2C_Stop_Condition(){
    SSPCON2bits.PEN = 1;
    I2C_Interrupt_Flag_Polling();
}

void I2C_Send_Data(uint8_t byte){
    SSPBUF = byte;
    I2C_Interrupt_Flag_Polling();
}

void I2C_Set_Receive_Mode(){
    SSPCON2bits.RCEN = 1;
}


uint8_t I2C_Read_Data(){
    I2C_Interrupt_Flag_Polling();
    while(!SSPSTATbits.BF);
    uint8_t Data = SSPBUF;
    return Data;
}

uint8_t I2C_Get_Ack_Stat_Bit(){
    return SSPCON2bits.ACKSTAT;
}

void I2C_Send_Aknowledge(){
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    I2C_Interrupt_Flag_Polling();
}

void I2C_Send_Not_Aknowledge(){
    SSPCON2bits.ACKDT = 1;
    SSPCON2bits.ACKEN = 1;
    I2C_Interrupt_Flag_Polling();
}

void I2C_Write_1_Byte_Register(uint8_t address,uint8_t reg,uint8_t data){
    uint8_t write_address = (address << 1) & ~I2C_WRITE_BIT;
    I2C_Open();
    I2C_Start_Condition();
    I2C_Send_Data(write_address);
    if(I2C_Get_Ack_Stat_Bit()){
        return;
    }
    
    I2C_Send_Data(reg);
    if(I2C_Get_Ack_Stat_Bit()){
        return;
    }
    
    I2C_Send_Data(data);
    if(I2C_Get_Ack_Stat_Bit()){
        return;
    }
    I2C_Stop_Condition();
    I2C_Close();
}

uint8_t I2C_Read_1_Byte_Register(uint8_t address,uint8_t reg){
    int status = 0;
    uint8_t Data;
    uint8_t Write_address = (address << 1) & ~(uint8_t)I2C_READ_BIT;
    uint8_t Read_address = (address << 1) | (uint8_t)I2C_READ_BIT;
    
    
    //##########################################################
    I2C_Open();
    I2C_Start_Condition();
    I2C_Send_Data(Write_address);
    if(I2C_Get_Ack_Stat_Bit()){
        status =1;
    }
    I2C_Send_Data(reg);
    if(I2C_Get_Ack_Stat_Bit()){
        status = 1;  
    }
    //##########################################################
    I2C_Start_Condition;
    I2C_Send_Data(Read_address);
    if(I2C_Get_Ack_Stat_Bit()){
        status = 1;  
    }
    //##########################################################
    I2C_Set_Receive_Mode();
    Data = I2C_Read_Data();
    I2C_Send_Not_Aknowledge();
    I2C_Stop_Condition();
    I2C_Close();
    return (Data);
}