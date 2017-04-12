/*
 * File:   cdk.c
 * Author: cuki
 *
 * Created on 20 de Março de 2017, 14:23
 */

#include "fuses.h"
#include "sys.h"
#include "rtcc.h"

#include <xc.h>
#include <libpic30.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

int main(void) {

    _TRISG8 = 0;
    LATG |= (1 << 8);
    RTCC_init();
    
    while (true) {
        ;
    }

    return 0;
}
