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
    uint32_t pos, res;
    float ang;
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
    __delay_ms(1500);

    if (encoder_ok) {
        res = 0;
        do {
            res = DSF60_get_resolution();
#ifdef DEBUG_UART1
            __C30_UART = 1;
            printf("Resolucao %lu\n", res);
            printf("Part Number %s\n", DSF60_get_partNumber());
            printf("Encoder Type %s\n", DSF60_get_encoderType());
            printf("Date Code %s\n", DSF60_get_dateCode());
#endif
            if (res == 0 || res > 10000)
                __delay_ms(1000);
        } while (res == 0 || res > 10000);
    }

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
            //            Nop();
            //            Nop();
            //            res = DSF60_get_resolution();
            Nop();
            Nop();
#ifdef DEBUG_UART1
            ang = ((float) pos) / ((float) res) * 360.0;
            __C30_UART = 1;
            printf("Pos %05lu %f\n", pos, (double) ang);
#endif
        }

        __delay_ms(1000);
    }
    return 0;
}