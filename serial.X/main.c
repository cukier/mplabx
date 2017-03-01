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
#define BAUDRATE    9600
#define BRGVAL      ((FCY/BAUDRATE)/16)-1

#include <libpic30.h>

//void __attribute__((__interrupt__, no_auto_psv)) _U1TXInterrupt(void) {
//    IFS0bits.U1TXIF = 0; // Clear TX Interrupt flag
////    U1TXREG = 'b'; // Transmit one character
//}

void uart_send(uint8_t c) {
    while (U1STAbits.UTXBF)
        ;
    
    U1TXREG = c;
    return;
}

int main(void) {

    U1MODEbits.STSEL = 0;
    U1MODEbits.PDSEL = 0;
    U1MODEbits.ABAUD = 0;
    U1MODEbits.BRGH = 0;

    U1BRG = BRGVAL;

    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX

    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;

    RPINR18bits.U1RXR = 0; // Assign U1RX To Pin RP0
    RPOR1bits.RP2R = 3; // Assign U1TX To Pin RP2

    while (1) {
        U1TXREG = 'c';
        __delay_ms(1000);
    }

    return 0;
}
