
#ifndef SERIAL_H
#define	SERIAL_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "sys.h"

#ifdef USE_UART_1
#ifdef BAUDRATE_1
#define BRGVAL_1            (((FCY/BAUDRATE_1)/16)-1)
#else
#error Definir BAUDRATE_1
#endif
#define U1_TX_RP            (RPOR6bits.RP12R)
#define U1_RX_RP            (11)
#endif

#ifdef USE_UART_2
#ifdef BAUDRATE_2
#define BRGVAL_2            (((FCY/BAUDRATE_2)/16)-1)
#else
#error Definir BAUDRATE_2
#endif
#define U2_TX_RP            (RPOR11bits.RP23R)
#define U2_RX_RP            (22)
#endif

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */   

#ifdef USE_UART_1
    void uart1_init(uint8_t *in_buffer);
    uint16_t uart1_get_index(void);
    bool uart1_get_rec(void);
    void uart1_set_rec(void);
#endif

#ifdef USE_UART_2
    void uart2_init(uint8_t *in_buffer);
    uint16_t uart2_get_index(void);
    bool uart2_get_rec(void);
    void uart2_set_rec(void);
#endif

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

