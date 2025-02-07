#ifndef I2C_H
#define I2C_H

#include <xc.h>

void OpenI2C(unsigned char sync_mode, unsigned char slew);
void CloseI2C(void);
void RestartI2C(void);
void StartI2C(void);
void StopI2C(void);
void AckI2C(void);
void NotAckI2C(void);
void IdleI2C(void);
void WriteI2C(unsigned char data_out);
unsigned char ReadI2C(void);

#endif