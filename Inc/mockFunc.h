#ifndef _MOCKFUNC_H
#define _MOCKFUNC_H
#include <stdint.h>


void Slave_Enable(uint8_t number);
void Slave_Disable(uint8_t number);
void SPI_SendReceive(uint8_t* datasend, uint8_t* dataReceive);
#endif // _MOCKFUNC_H
