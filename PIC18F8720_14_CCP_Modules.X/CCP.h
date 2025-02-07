#include "Config.h"

void PWM_1_Initialize(void){
    CCP1CONbits.CCP1M0 = 1;
    CCP1CONbits.CCP1M1 = 1;
    CCP1CONbits.CCP1M2 = 1;
    CCP1CONbits.CCP1M3 = 1;
    CCP1CONbits.DC1B0 = 0;
    CCP1CONbits.DC1B1 = 0;
    
}

void PWM_2_Initialize(void){
    CCP2CONbits.CCP2M0 = 1;
    CCP2CONbits.CCP2M1 = 1;
    CCP2CONbits.CCP2M2 = 1;
    CCP2CONbits.CCP2M3 = 1;
    CCP2CONbits.DC2B0 = 0;
    CCP2CONbits.DC2B1 = 0;
}


void Capture_1_Initialize(void){

}

void Capture_1_Initialize(void){

}

void Compare_1_Initialize(void){

}

void Compare_1_Initialize(void){

}