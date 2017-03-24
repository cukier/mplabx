/*
 * File:   main.c
 * Author: cuki
 *
 * Created on 1 de Mar�o de 2017, 11:33
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
#include "uart.h"

#include <libpic30.h>
#include <stdio.h>
#include <stdbool.h>
#include <xc.h>
#include <p24FJ1024GB606.h>
#include <stdint.h>

int main(void) {
    uint8_t data[3] = {1, 2, 3};

    initUart_1();
    initUart_2();
    initUart_3();

    while (1) {
        sendFrom_1(data, 3);
        sendFrom_2(data, 3);
        sendFrom_3(data, 3);
        __delay_ms(1000);
    }

    return 0;
}
