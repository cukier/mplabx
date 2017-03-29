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
    bool uart1_send(uint8_t *data, uint16_t size);
    uint16_t uart1_get(uint8_t *data, uint16_t size);
    bool uart2_send(uint8_t *data, uint16_t size);
    uint16_t uart2_get(uint8_t *data, uint16_t size);
    bool uart3_send(uint8_t *data, uint16_t size);
    uint16_t uart3_get(uint8_t *data, uint16_t size);
    uint16_t uart3_getRxSize(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

