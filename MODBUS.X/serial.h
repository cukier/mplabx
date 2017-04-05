#ifndef SERIAL_H
#define	SERIAL_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "sys.h"

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */   
    
    void uart_init(void);
#ifdef USE_UART_1    
    bool uart1_send(uint8_t *data, uint16_t size);
    uint16_t uart1_get(uint8_t *data, uint16_t size);
#endif
#ifdef USE_UART_2
    bool uart2_send(uint8_t *data, uint16_t size);
    uint16_t uart2_get(uint8_t *data, uint16_t size);
    uint16_t uart2_getRxSize(void);
#endif
#ifdef USE_UART_3    
    bool uart3_send(uint8_t *data, uint16_t size);
    uint16_t uart3_get(uint8_t *data, uint16_t size);
    uint16_t uart3_getRxSize(void);
#endif    

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

