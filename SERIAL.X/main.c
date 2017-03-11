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
#include <libpic30.h>
#include <stdio.h>
#include <stdbool.h>
#include <xc.h>
#include <p24FJ1024GB606.h>
#include <stdint.h>
#include "serial.h"

int main(void) {  
    uint8_t buff[SERIAL_BUFFER_SIZE] = { 0 };
    uint8_t buff2[SERIAL_BUFFER_SIZE] = { 0 };
    uint16_t cont;
    uint16_t cont2;

    uart1_init(buff);
    uart2_init(buff2);

    while (1) {
        __C30_UART = 1;
        if (uart1_get_rec()) {
            uart1_set_rec();
            cont = 0;
            
            while (cont < uart1_get_index())
                putchar(buff[cont++]);
            
            printf("_1");
        }
        __C30_UART = 2;        
        if (uart2_get_rec()) {
            uart2_set_rec();
            cont2 = 0;
            
            while (cont2 < uart2_get_index())
                putchar(buff2[cont2++]);
            
            printf("_2");
        }
        
        
    }

    return 0;
}
