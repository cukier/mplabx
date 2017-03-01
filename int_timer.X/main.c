/*
 * File:   main.c
 * Author: cuki
 *
 * Created on 1 de Março de 2017, 09:25
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

#define FOSC    (16000000ULL)
#define FCY     (FOSC/2)

#include <libpic30.h>

void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void) {
    LATEbits.LATE5 = ~LATEbits.LATE5;
    _T1IF = 0;
}

int main(void) {        
    TRISEbits.TRISE5 = 0;
    
    T1CON = 0;
    T1CONbits.TCKPS = 3; //1:256
    
    _T1IP = 1; //prioriedade interrupcao timer 1 alta
    _T1IF = 0; //limpa flag de disparo timer 1
    _T1IE = 1; //habilita interrupcao timer 1
    PR1 = 30000; //periodo timer 1
    //tempo = 2 x PR1 x TCKPS / FOSC
    //tempo = 2 x 30000 x 256 / 16000000
    
    T1CONbits.TON = 1;
    
    while (1) {
    }
    
    return 0;
}
