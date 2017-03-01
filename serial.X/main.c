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

#include <xc.h>
#include <p24FJ1024GB606.h>
#include <stdint.h>

#define FOSC        (16000000ULL)
#define FCY         (FOSC/2)
#define BAUDRATE    (9600)
#define BRGVAL      (((FCY/BAUDRATE)/16)-1)

#include <libpic30.h>
#include <stdio.h>

void uart_init(void) {
    U1MODEbits.STSEL = 0; // 1 stop bit
    U1MODEbits.PDSEL = 0; // 8-bit data, no parity
    U1MODEbits.ABAUD = 0; // Baud rate measurement is disabled or completed
    U1MODEbits.BRGH = 0; // Standard Speed mode

    U1BRG = BRGVAL; //Baudrate

    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX
    U1MODEbits.UARTEN = 1; // UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>
    U1STAbits.UTXEN = 1; // Transmit is enabled, UxTX pin is controlled by UARTx

    RPINR18bits.U1RXR = 0; // Assign U1RX To Pin RP0
    RPOR1bits.RP2R = 3; // Assign U1TX To Pin RP2
    __C30_UART = 1; // printf
}

int main(void) {
    uint8_t cont;

    uart_init();

    while (1) {
        printf("Hello %u\n", cont++);
        __delay_ms(500);
    }

    return 0;
}
