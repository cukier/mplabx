#ifndef UART2_H
#define UART2_H

#include "uart.h"

void initUart_2(void);
bool sendFrom_2(const uint8_t* startOfData, uint16_t bytesToSend);
#endif /* UART2_H */
