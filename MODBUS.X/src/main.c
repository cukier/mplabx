/*
 * File:   cdk.c
 * Author: cuki
 *
 * Created on 20 de Março de 2017, 14:23
 */

#include "fuses.h"
#include "sys.h"

#include <libpic30.h>
#include <stdio.h>

int main(void) {

    sys_init();

    while (true) {
        sys_pooling();
    }

    return 0;
}
