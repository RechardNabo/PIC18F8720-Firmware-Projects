

//set the configuration bits for PIC 18F8720

// PIC18F8720 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator with PLL enabled; clock frequency = (4 x FOSC))
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config BORV = 25        // Brown-out Reset Voltage bits (VBOR set to 2.5V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG3L
#pragma config MODE = MC        // Processor Mode Select bits (Microcontroller mode)
#pragma config WAIT = OFF       // External Bus Data Wait Enable bit (Wait selections unavailable for table reads and table writes)

// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Low-Voltage ICSP Enable bit (Low-voltage ICSP enabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)
#pragma config CP4 = OFF        // Code Protection bit (Block 4 (010000-013FFFh) not code-protected)
#pragma config CP5 = OFF        // Code Protection bit (Block 5 (014000-017FFFh) not code-protected)
#pragma config CP6 = OFF        // Code Protection bit (Block 6 (018000-01BFFFh) not code-protected)
#pragma config CP7 = OFF        // Code Protection bit (Block 7 (01C000-01FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)
#pragma config WRT4 = OFF       // Write Protection bit (Block 4 (010000-013FFFh) not write-protected)
#pragma config WRT5 = OFF       // Write Protection bit (Block 5 (014000-017FFFh) not write-protected)
#pragma config WRT6 = OFF       // Write Protection bit (Block 6 (018000-01BFFFh) not write-protected)
#pragma config WRT7 = OFF       // Write Protection bit (Block 7 (01C000-01FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR4 = OFF      // Table Read Protection bit (Block 4 (010000-013FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR5 = OFF      // Table Read Protection bit (Block 5 (014000-017FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR6 = OFF      // Table Read Protection bit (Block 6 (018000-01BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR7 = OFF      // Table Read Protection bit (Block 7 (01C000-01FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#include <stdio.h>
#include <stdint.h>


#define _XTAL_FREQ 20E6

//TC74 I2C device address
#define TC74_ADDR 0x90

//TC74 device commands
#define TC74_READ_TEMP 0x00
#define TC74_READ_CONF 0x01
#define TC74_WRITE_CONF 0x02

//TC74 device configuration register value
#define TC74_CONFIG 0x00

//TC74 device wake-up time in ms
#define TC74_WAKEUP_TIME 20

//Variables
uint8_t temp_data;

//Function Prototypes
void init_TC74_I2C(void);
void write_TC74_reg(uint8_t, uint8_t);
uint8_t read_TC74_reg(uint8_t);
uint8_t read_TC74_temp();

//Main program
int main(void)
{
    TRISD = 0x00;
    init_TC74_I2C();
    while(1){
        write_TC74_reg(TC74_WRITE_CONF, TC74_CONFIG);
        __delay_ms(TC74_WAKEUP_TIME);
        PORTD  = (unsigned char)read_TC74_temp();
        __delay_ms(1000);
    }
    
    return 0;
}

//Function definitions
void init_TC74_I2C(void)
{
    TRISC3 = 1; //SCL Pin as input
    TRISC4 = 1; //SDA Pin as input

    SSPCON1 = 0b00110110; //Enable I2C and set as Master
    SSPCON2 = 0x00;
    SSPADD = 0x09; //100 kHz Baud Rate (Fosc/4 * (SSPADD + 1))
    SSPSTAT = 0b10000000; //Set Slew Rate Control
}

void write_TC74_reg(uint8_t reg_addr, uint8_t data)
{
    SSPCON2bits.SEN = 1; //Initiate Start Condition
    while(SSPCON2bits.SEN); //Wait for Start Condition to finish

    SSPBUF = TC74_ADDR; //Send Device Address (Write)
    while(SSPSTATbits.BF); //Wait for Address to finish transmitting

    SSPBUF = reg_addr; //Send register address
    while(SSPSTATbits.BF); //Wait for Address to finish transmitting

    SSPBUF = data; //Send data
    while(SSPSTATbits.BF); //Wait for data to finish transmitting

    SSPCON2bits.PEN = 1; //Initiate Stop Condition
    while(SSPCON2bits.PEN); //Wait for Stop Condition to finish
}

uint8_t read_TC74_reg(uint8_t reg_addr)
{
    SSPCON2bits.SEN = 1; //Initiate Start Condition
    while(SSPCON2bits.SEN); //Wait for Start Condition to finish

    SSPBUF = TC74_ADDR; //Send Device Address (Write)
    while(SSPSTATbits.BF); //Wait for Address to finish transmitting

    SSPBUF = reg_addr; //Send register address
    while(SSPSTATbits.BF); //Wait for Address to finish transmitting

    SSPCON2bits.RSEN = 1; //Initiate Repeat Start Condition
    while(SSPCON2bits.RSEN); //Wait for Repeat Start Condition to finish

    SSPBUF = TC74_ADDR | 0x01; //Send Device Address (Read)
    while(SSPSTATbits.BF); //Wait for Address to finish transmitting

    SSPCON2bits.RCEN = 1; //Enable Receive Mode
    while(!SSPSTATbits.BF); //Wait for data to be available in buffer
    temp_data = SSPBUF; //Read data

    SSPCON2bits.ACKDT = 1; //Send NACK
    SSPCON2bits.ACKEN = 1; //Initiate ACK sequence
    while(SSPCON2bits.ACKEN); //Wait for ACK sequence to finish

    SSPCON2bits.PEN = 1; //Initiate Stop Condition
    while(SSPCON2bits.PEN); //Wait for Stop Condition to finish

    return temp_data;
}

uint8_t read_TC74_temp()
{
    uint8_t temp;
    temp = read_TC74_reg(TC74_READ_TEMP);
    return  temp;
    
}