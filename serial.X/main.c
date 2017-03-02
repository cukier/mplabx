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
#include <stdbool.h>

#define BUFFER_SIZE     512

uint16_t buff_index, buff_rec;
uint8_t buffer[BUFFER_SIZE];

void __attribute__ ((interrupt,no_auto_psv)) _U1RXInterrupt(void) {
    buffer[buff_index++] = U1RXREG;
    
    if (buff_index >= BUFFER_SIZE)
        buff_index = 0;
    
    T1CONbits.TCKPS = 1; //1:8
    IFS0bits.U1RXIF = 0; //limpa flag int rx     
    T1CONbits.TON = 1; //liga timer 1
    PR1 = UINT16_MAX; //periodo timer 1
}

void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void) {
    T1CONbits.TON = 0; //desliga timer    
    _T1IF = 0; //deliga flag interrupcao
    buff_rec = buff_index;
    buff_index = 0;
}

void tmr1_init() {
    T1CON = 0; //limpa registrador    
    _T1IP = 1; //prioriedade interrupcao timer 1 alta    
    _T1IF = 0; //limpa flag de disparo timer 1
    _T1IE = 1; //habilita interrupcao timer 1
    PR1 = 65535;
    //tempo = 2 x PR1 x TCKPS / FOSC
    //tempo = 2 x 30000 x 256 / 16000000
    return;
}

void uart_init(void) {
    buff_index = 0;
    
    U1MODEbits.STSEL = 0; // 1 stop bit
    U1MODEbits.PDSEL = 0; // 8-bit data, no parity
    U1MODEbits.ABAUD = 0; // Baud rate measurement is disabled or completed
    U1MODEbits.BRGH = 0; // Standard Speed mode

    U1BRG = BRGVAL; //Baudrate

    U1MODEbits.UARTEN = 0; // UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>    
    U1STAbits.UTXEN = 0; // Transmit is enabled, UxTX pin is controlled by UARTx
    U1STAbits.URXEN = 0; // Recive is enabled
    
    IFS0bits.U1RXIF = 0; //limpa falg int rx1
    IEC0bits.U1RXIE = 1; //habilita interrupcao rx1  
    
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;

    //__builtin_write_OSCCONL(OSCCON & 0xbf); // Unlock Registers
    RPINR18bits.U1RXR = 4; // Assign U1RX To Pin RP4
    RPOR1bits.RP2R = 3; // Assign U1TX To Pin RP2
    __C30_UART = 1; // printf
    
    tmr1_init();
    
    U1MODEbits.UARTEN = 1;
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
