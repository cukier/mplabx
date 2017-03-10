
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
#define U1_RX_RP            (11)
#define U1_TX_RP            (RPOR6bits.RP12R)

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */   

    void uart_init(uint8_t *in_buffer);
    uint16_t uart_get_index(void);
    bool uart_get_rec(void);
    void uart_set_rec(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

