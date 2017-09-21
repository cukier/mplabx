/*
 * File:   heart_beat.c
 * Author: cuki
 *
 * Created on 17 de Abril de 2017, 08:31
 */

#include "heart_beat.h"

#include <stdint.h>
#include <libpic30.h>

void hb_init(void) {

    _TRISG8 = 0;
    _LATG8 = 1;

    return;
}

void hb_beat(uint32_t ms) {

    if (ms == 0)
        return;

    _LATG8 = !_LATG8;
    __delay_ms(ms);
}