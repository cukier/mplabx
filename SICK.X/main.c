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

    pos = 0;
    encoder_ok = false;

    DSF60_init_encoder();
    __delay_ms(100);

    while (true) {

        if (!encoder_ok) {
            encoder_ok = DSF60_check();
            Nop();
            Nop();
        } else {
            pos = DSF60_get_position();
            Nop();
            Nop();
        }

        __delay_ms(1000);
    }
    return 0;
}