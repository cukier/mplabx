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

typedef struct {
    void (*baudrate)(uint16_t baudrate);
    int (*copy)(uint8_t* storageBuffer, int maxBytesToRead);
    void (*drop)(int bytesToDrop);
    void (*flush)(void);
    uint16_t(*size)(void);
    bool(*send)(const uint8_t* startOfData, uint16_t bytesToSend);
    int (*receive)(uint8_t* storageBuffer, int maxBytesToRead);
    void (*init)(void);
} Uart;

#endif /* UART_H */
