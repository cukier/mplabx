#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "sys.h"

#define _ISR_ void __attribute__((interrupt, no_auto_psv))
#define OFF 0
#define ON  1
#define YES 1

void initUart_1(void);
bool sendFrom_1(const uint8_t* startOfData, uint16_t bytesToSend);

void initUart_2(void);
bool sendFrom_2(const uint8_t* startOfData, uint16_t bytesToSend);

void initUart_3(void);
bool sendFrom_3(const uint8_t* startOfData, uint16_t bytesToSend);

#endif /* UART_H */
