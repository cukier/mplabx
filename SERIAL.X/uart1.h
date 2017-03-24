#ifndef UART1_H
#define UART1_H

#include "uart.h"

void initUart_1(void);
bool sendFrom_1(const uint8_t* startOfData, uint16_t bytesToSend);

#endif /* UART1_H */
