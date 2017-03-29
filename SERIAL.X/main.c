/*
 * File:   main.c
 * Author: cuki
 *
 * Created on 1 de Março de 2017, 11:33
 */
#pragma config BWRP = OFF
#pragma config BSS = DISABLED
#pragma config BSEN = OFF
#pragma config GWRP = OFF
#pragma config GSS = DISABLED
#pragma config CWRP = OFF
#pragma config CSS = DISABLED
#pragma config AIVTDIS = OFF
#pragma config BSLIM = 0x1FFF
#pragma config FNOSC = PRI
#pragma config PLLMODE = DISABLED
#pragma config IESO = ON
#pragma config POSCMD = HS
#pragma config OSCIOFCN = OFF
#pragma config SOSCSEL = ON
#pragma config PLLSS = PLL_PRI
#pragma config IOL1WAY = ON
#pragma config FCKSM = CSDCMD
#pragma config WDTPS = PS32768
#pragma config FWPSA = PR128
#pragma config FWDTEN = ON
#pragma config WINDIS = OFF
#pragma config WDTWIN = WIN25
#pragma config WDTCMX = WDTCLK
#pragma config WDTCLK = LPRC
#pragma config BOREN = ON
#pragma config LPCFG = OFF
#pragma config DNVPEN = ENABLE
#pragma config ICS = PGD1
#pragma config JTAGEN = OFF
#pragma config BTSWP = OFF
#pragma config ALTCMPI = DISABLE
#pragma config TMPRPIN = OFF
#pragma config SOSCHP = ON
#pragma config ALTVREF = ALTREFEN

#include "sys.h"
#include "serial.h"

#include <libpic30.h>
#include <stdio.h>
#include <stdbool.h>
#include <xc.h>
#include <p24FJ1024GB606.h>
#include <stdint.h>

int main(void) {
    uint16_t n;
    uint8_t data[3] = {1, 2, 3};
    uint8_t rcv[3] = {0};
    uint8_t rcv2[3] = {0};
    uint8_t rcv3[3] = {0};

    uart_init();

    while (1) {
        n = 0;
        uart1_send(data, 3);
        n = uart1_get(rcv, 3);

        if (n != 0)
            n = 0;

        n = 0;
        uart2_send(data, 3);
        n = uart2_get(rcv2, 3);

        if (n != 0)
            n = 0;

        n = 0;
        uart3_send(data, 3);
        n = uart3_get(rcv3, 3);

        if (n != 0)
            n = 0;

        __delay_ms(1000);
    }

    return 0;
}
