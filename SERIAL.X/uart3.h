#ifndef UART3_H
#define UART3_H

#include "uart.h"

void initUart_3(void);
bool sendFrom_3(const uint8_t* startOfData, uint16_t bytesToSend);
#endif /* UART3_H */
