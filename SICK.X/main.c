/*
 * File:   main.c
 * Author: cuki
 *
 * Created on 8 de Março de 2017, 12:45
 */

#include "fuses.h"
#include "sys.h"
#include "serial.h"
#include "sick.h"
#include <xc.h>
#include <libpic30.h>
#include <p24FJ1024GB606.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    bool encoder_ok;
    uint32_t pos;
#ifdef DEBUG_UART1
    uint8_t debug_buffer[SERIAL1_BUFFER_SIZE];
#endif

    pos = 0;
    encoder_ok = false;

#ifdef DEBUG_UART1
    uart1_init(debug_buffer);
#endif

    DSF60_init_encoder();
    __delay_ms(100);
#ifdef DEBUG_UART1
    __C30_UART = 1;
    printf("Begin\n");
#endif    
    encoder_ok = DSF60_check();

    while (true) {

        if (!encoder_ok) {
            //            encoder_ok = DSF60_check();
            Nop();
            Nop();
#ifdef DEBUG_UART1
            __C30_UART = 1;
            printf("Encoder no ok\n");
#endif
        } else {
            Nop();
            Nop();
            pos = DSF60_get_position();
            Nop();
            Nop();
#ifdef DEBUG_UART1
            __C30_UART = 1;
            printf("Pos %lu\n", pos);
#endif
        }

        __delay_ms(1000);
    }
    return 0;
}