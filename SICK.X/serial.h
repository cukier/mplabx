
#ifndef SERIAL_H
#define	SERIAL_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef SERIAL_BUFFER_SIZE
#define SERIAL_BUFFER_SIZE  (512)
#endif
#ifndef FOSC
#define FOSC                (16000000ULL)
#endif
#ifndef FCY
#define FCY                 (FOSC/2)
#endif
#ifndef BAUDRATE
#define BAUDRATE            (9600)
#endif
#define BRGVAL              (((FCY/BAUDRATE)/16)-1)
#ifndef U1_RX_RP
#define U1_RX_RP            (11)
#endif
#ifndef U1_TX_RP
#define U1_TX_RP            (RPOR6bits.RP12R)
#endif
#ifndef U2_RX_RP
#define U2_RX_RP            (11)
#endif
#ifndef U2_TX_RP
#define U2_TX_RP            (RPOR6bits.RP12R)
#endif

#define USE_UART_2

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

